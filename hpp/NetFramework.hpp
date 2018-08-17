#ifndef NET_FRAMEWORK
#define NET_FRAMEWORK

#include <SFML/Network.hpp>
#include <map>

class NetFramework
{
public:
    NetFramework();
    ~NetFramework();

    void setHost(std::string host);
    void addData(std::string field, std::string data);
    void removeData(std::string field);
    sf::Http::Response sendData();
    bool saveConfig(std::string filename);
    bool loadConfig(std::string filename);
    bool saveData(std::string filename);
    bool loadData(std::string filename);
    void setMethod(int method);
    void setUri(std::string uri);
    void setPort(int port);
    std::string getHost();
    int getPort();
    int getMethod();
    std::string getUri();
private:
    std::map<std::string,std::string> fields;
    std::string host;
    int method;
    int port;
    std::string uri;

    sf::Http http;
    sf::Http::Request request;
    sf::Http::Response response;
};

#endif // NET_FRAMEWORK
