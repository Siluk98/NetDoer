#include <iostream>

#include "hpp/menu_handler.hpp"
#include "hpp/PageDownloader.hpp"
#include "hpp/menu_handler.hpp"


int main(int argc, char** argv)
{
    NetFramework* net = new NetFramework;
    PageDownloader pd(net);

    bool automatic = true;

    if(argc==3)
    {
        net->setHost(argv[1]);
        net->setUri(argv[2]);
        automatic = false;
        pd.downloadAll();
    }

    while(automatic)
    {
    std::cout << "1. Set host" << std::endl;
    std::cout << "2. Add data" << std::endl;
    std::cout << "3. Config" << std::endl;
    std::cout << "4. Send data" << std::endl;
    std::cout << "5. Download domain" << std::endl;

    int choice;
    std::cin >> choice;


    switch(choice)
    {
        case 1:
        {
            std::string host;
            std::cin >> host;
            net->setHost(host);
            break;
        }
        case 2:
        {
            std::string f,d;
            std::cin >> f;
            std::cin >> d;
            net->addData(f,d);
            break;
        }
        case 3:
        {
            config(*net);
            break;
        }
        case 4:
        {
            std::cout << net->sendData().getBody();
            break;
        }
        case 5:
        {
            pd.downloadAll();
            break;
        }
        default:
        {
            break;
        }
    }
    }
    return 0;
}
