#ifndef MENU_H
#define MENU_H

#include "NetFramework.hpp"

void method(NetFramework& net)
{
    std::cout << "1. GET" << std::endl;
    std::cout << "2. POST" << std::endl;
    std::cout << "3. HEAD" << std::endl;
    std::cout << "4. PUT" << std::endl;
    std::cout << "5. DELETE" << std::endl;

    int c;
    std::cin >> c;
    net.setMethod(c-1);
}

void config(NetFramework& net)
{
    std::cout << "1. Set Method" << std::endl;
    std::cout << "2. Set URI" << std::endl;
    std::cout << "3. Set port" << std::endl;
    std::cout << "4. Save config" << std::endl;
    std::cout << "5. Load config" << std::endl;
    std::cout << "6. Save data" << std::endl;
    std::cout << "7. Load data" << std::endl;

    int c;
    std::cin >> c;

    switch(c)
    {
        case 1:
        {
            method(net);
            break;
        }
        case 2:
        {
            std::string s;
            std::cin >> s;
            net.setUri(s);
            break;
        }
        case 3:
        {
            int i;
            std::cin >> i;
            net.setPort(i);
            break;
        }
        case 4:
        {
            std::string s;
            std::cin >> s;
            net.saveConfig(s);
            break;
        }
        case 5:
        {
            std::string s;
            std::cin >> s;
            net.loadConfig(s);
            break;
        }
        case 6:
        {
            std::string s;
            std::cin >> s;
            net.saveData(s);
            break;
        }
        case 7:
        {
            std::string s;
            std::cin >> s;
            net.loadData(s);
            break;
        }
        default:
        {
            break;
        }
    }
}

#endif // MENU_H
