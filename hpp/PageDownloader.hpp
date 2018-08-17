#ifndef PAGEDOWNLOADER_H
#define PAGEDOWNLOADER_H

#include "NetFramework.hpp"
#include <SFML/Network.hpp>

class PageDownloader
{
public:
    PageDownloader(NetFramework*);
    ~PageDownloader();
    void downloadAll();
    void processResponse(sf::Http::Response&, std::string);
    void savePage(std::string,std::string);
private:
    NetFramework* net;
    std::vector<std::string> served;
    std::vector<std::string> todo;
    void mkdir(std::string);
    void parseLink(std::string);
    void extractLinks(std::string, std::string, std::string, std::string);
    void getForm(std::string);
};

#endif // PAGEDOWNLOADER_H
