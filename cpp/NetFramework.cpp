#include "../hpp/NetFramework.hpp"
#include <fstream>
#include <iostream>


NetFramework::NetFramework(){
    port = 0;
    method = 0;
    host = "/";
    uri = "/";
    setHost(host);
    setMethod(method);
    setUri(uri);
}
NetFramework::~NetFramework(){}

void NetFramework::setHost(std::string host)
{
    this->host = host;
    http.setHost(host,port);
}

void NetFramework::addData(std::string field, std::string data)
{
    fields[field] = data;
}

void NetFramework::removeData(std::string field)
{
    fields.erase(field);
}

sf::Http::Response NetFramework::sendData()
{
    for(auto i:fields)
    {
        request.setField(i.first, i.second);
    }
    response = http.sendRequest(request);
    return response;
}

bool NetFramework::saveConfig(std::string filename)
{
    std::fstream file;
    file.open(filename.c_str(),std::ios::out|std::ios::trunc);
    if(file.good())
    {
        return true;
    }
    else
    {
        std::cout << "failed to save config" << std::endl;
        return false;
    }
}

bool NetFramework::loadConfig(std::string filename)
{
    std::fstream file;
    file.open(filename.c_str(),std::ios::in);
    if(file.good())
    {
        return true;
    }
    else
    {
        std::cout << "failed to load config" << std::endl;
        return false;
    }
}

bool NetFramework::saveData(std::string filename)
{
    std::fstream file;
    file.open(filename.c_str(),std::ios::out|std::ios::trunc);
    if(file.good())
    {
        return true;
    }
    else
    {
        std::cout << "failed to save data" << std::endl;
        return false;
    }
}

bool NetFramework::loadData(std::string filename)
{
    std::fstream file;
    file.open(filename.c_str(),std::ios::in);
    if(file.good())
    {
        return true;
    }
    else
    {
        std::cout << "failed to load data" << std::endl;
        return false;
    }
}

void NetFramework::setMethod(int method)
{
    sf::Http::Request::Method m = static_cast<sf::Http::Request::Method>(method);
    request.setMethod(m);
    this->method = method;
    /*
    switch(method)
    {
        case 0:
        {
            request.setMethod(sf::Http::Request::Get);
            break;
        }
        case 1:
        {
            request.setMethod(sf::Http::Request::Post);
            break;
        }
        case 2:
        {
            request.setMethod(sf::Http::Request::Put);
            break;
        }
        case 3:
        {
            request.setMethod(sf::Http::Request::Delete);
            break;
        }
        case 4:
        {
            request.setMethod(sf::Http::Request::Head);
            break;
        }
        default:
        {
            throw;
            break;
        }
    }
    */
}

void NetFramework::setUri(std::string uri)
{
    this->uri = uri;
    request.setUri(uri);
}

void NetFramework::setPort(int port)
{
    this->port = port;
    http.setHost(host, port);
}

std::string NetFramework::getHost()
{
    return host;
}

int NetFramework::getMethod()
{
    return method;
}

std::string NetFramework::getUri()
{
    return uri;
}

int NetFramework::getPort()
{
    return port;
}
