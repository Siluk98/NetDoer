#include "../hpp/PageDownloader.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <regex>

#include <windows.h> // zmienic w cpp17

PageDownloader::PageDownloader(NetFramework * arg)
{
    net = arg;
}

PageDownloader::~PageDownloader()
{
    //delete http;
}

void PageDownloader::downloadAll()
{
    net->setMethod(0);
    served.push_back(net->getUri());
    todo.push_back(net->getUri());
    while(!todo.empty())
    {
        net->setUri(todo.front());
        sf::Http::Response res = net->sendData();
        processResponse(res, todo.front());
        served.push_back(todo.front());
        todo.erase(todo.begin());
        /*
        for(auto a:todo)
        {
            std::cout << a << std::endl;
        }
        */
    }
}

void PageDownloader::processResponse(sf::Http::Response& res, std::string name)
{
    std::string body = res.getBody();
    std::cout << "body: " << body << std::endl;
    savePage(name, body);
    extractLinks("<a ","</a>","href", body);
    extractLinks("<link ",">", "href", body);
    extractLinks("<script ",">", "src", body);
    getForm(body);
}

void PageDownloader::savePage(std::string name, std::string body)
{
    std::fstream file;
    name.erase(0,1);
    if(name.empty())
    {
        name = "index";
    }
    std::string namef = net->getHost();
    namef.append("\\");
    namef.append(name);
    std::replace(namef.begin(),namef.end(),'.','_');
    std::replace(namef.begin(),namef.end(),'/','\\');
    std::replace(namef.begin(),namef.end(),'?','_');
    std::replace(namef.begin(),namef.end(),'<','_');
    std::replace(namef.begin(),namef.end(),'>','_');
    std::replace(namef.begin(),namef.end(),'|','_');
    std::replace(namef.begin(),namef.end(),':','_');
    std::replace(namef.begin(),namef.end(),'*','_');
    std::replace(namef.begin(),namef.end(),'"','_');
    namef.append(".html");
    //std::replace(namef.begin(),namef.end(),';','_');
    //std::replace(namef.begin(),namef.end(),'&','_');
    //std::replace(namef.begin(),namef.end(),'=','_');
    mkdir(namef);
    std::cout << namef << std::endl;
    file.open(namef.c_str(), std::ios::out|std::ios::trunc);
    if(file.good())
    {
        file << body;
    }
    else
    {
        std::cout << "Failed to save page" << std::endl;
    }
    file.close();
}

void PageDownloader::mkdir(std::string path)
{
    std::string command = "mkdir ";
    for(int i=path.size()-1;i>=0;i--)
    {
        if(path[i] == '\\')
        {
            command.append(path.substr(0,i));
            break;
        }
    }
    std::cout << command << std::endl;
    system(command.c_str());
}

void PageDownloader::parseLink(std::string s)
{
    std::string uri = "";
    int p = s.find(net->getHost());
    if(p!=(-1))
    {
        uri = s.substr(p+net->getHost().size(), s.size());
        //std::cout << uri << std::endl;
    }
    else
    {
        if((int)s.find("http") == (-1) && (int)s.find("www") == (-1) && s[0]!='#')
        {
            if(s.substr(0,2) == "..")
                uri = this->net->getUri() + "/" + s;
            else
                uri = s;
        }
    }

    bool isServed = false;
    for(auto i:served)
    {
        if(i == uri)
        {
            isServed = true;
            break;
        }
    }

    if(!uri.empty() && !isServed)
    {
        todo.push_back(uri);
    }
}

void PageDownloader::extractLinks(std::string st, std::string fin, std::string atr, std::string body)
{
    //bool html_flag = true;
    //std::cout << body << std::endl << std::endl;

    //std::string body_copy = body;
    std::string q = st+".*?"+fin;
    std::cout << q << std::endl;
    std::regex reg(q);
    std::smatch match;
    std::vector<std::string> links;
    while(std::regex_search(body, match, reg)){
        std::cout << match.str() << std::endl;
        links.push_back(match.str());
        body = match.suffix();
    }

    std::regex lreg(atr+"=\".*?\"");
    for(unsigned int i=0;i<links.size();i++)
    {
        if(std::regex_search(links[i],match,lreg))
        {
            links[i] = match.str();
            links[i].erase(0,atr.size()+2);
            links[i].erase(links[i].size()-1,1);
            std::cout << links[i] << std::endl;
        }
        else
        {
            links.erase(links.begin()+i);
            i--;
        }
    }

    for(unsigned int i=0;i<links.size();i++) parseLink(links[i]);
    /*
    while(html_flag)
    {
        int start = body.find(st);
        if(start==(-1)) break;
        body_copy = body_copy.substr(start);
        int end = body_copy.find(fin);
        if(end==(-1)) break;
        //std::cout << start << " " << end << std::endl;

        std::string s = body_copy.substr(0, end);
        int ps = s.find("href=\"");
        s = s.substr(ps+6,s.size());
        int pe = s.find('"');
        s = s.substr(0,pe);

        std::cout << "156: " << s << std::endl;

        parseLink(s);

        body = body.substr(end+4, body.size());
        //std::cout << body << std::endl;
        body_copy = body;
    }
    */
}

std::vector<std::string> regFind(std::string text, std::string reg)
{
    std::vector<std::string> ret;
    try
    {
        std::cout << "a";
        std::regex reg1(reg);
        std::cout << "b";
        std::smatch m;
        std::cout << "c";
        while(std::regex_search(text, m, reg1))
        {
            std::cout << "d";
            ret.push_back(m.str());
            std::cout << "e";
            std::cout << m.suffix();
            text = m.suffix();
        }
        std::cout << "f";
    }
    catch(const std::regex_error& e)
    {
        std::cout << e.what();
        if (e.code() == std::regex_constants::error_complexity)
        std::cout << "The complexity of an attempted match against a regular expression exceeded a pre-set level.\n";
        else if (e.code() == std::regex_constants::error_stack)
        std::cout << "There was insufficient memory to determine whether the regular expression could match the specified character sequence.\n";

    }
    std::cout << "g";
    return ret;
}

void PageDownloader::getForm(std::string body)
{
    std::cout << "Forms:" << std::endl;
    std::vector<std::string> forms = regFind(body, "<form(.*?)>((.|\n)*?)</form>");
    std::cout << forms.size() << std::endl;
    std::cout << "t2";

    for(const auto &j:forms)
    {
        std::cout << "Form encountered ([Y]es/[N]o/[S]kip): ";
        char x;
        std::cin >> x;
        switch(x)
        {
            case 'y':{}
            case 'Y':{break;}
            case 'n':{}
            case 'N':{
                return;
                break;
                }
            case 's':{}
            case 'S':{
                continue;
                break;
                }
            default:{
                continue;
            }
        }

        std::vector<std::string> act = regFind(j,"action=\(.*?)\"");

        //std::regex ract("action=\(.*?)\"");
        //std::smatch mact;
        std::string action;
        if(act.size() != 0)
            action = act[0];
        else action = this->net->getUri();

        auto met = regFind(j, "method=\"(.*?)\"");
        if(met.size() != 0)
        {
            int mcast = 0;
            std::string mcasts = met[0];
            for (auto &c: mcasts) c = std::tolower(c);
            if(mcasts == "get") mcast = 0;
            else if(mcasts == "post") mcast = 1;
            else if(mcasts == "head") mcast = 2;
            else if(mcasts == "put") mcast = 3;
            else if(mcasts == "delete") mcast = 4;
            else mcast = 0;
            net->setMethod(mcast);
        }
        else net->setMethod(0);

        std::cout << "action: " << action << std::endl;
        std::cout << j << std::endl;

        std::vector<std::string> inp = regFind(j,"<input(.*?)>");
        for(auto k: inp)
        {

        }
    }
}
