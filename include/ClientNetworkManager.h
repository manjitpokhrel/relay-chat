#ifndef CLIENTNETWORKMANAGER_H
#define CLIENTNETWORKMANAGER_H

#include <string>
#include <map>

class ClientNetworkManager {
public:
    explicit ClientNetworkManager(const std::string& serverUrl);
    ~ClientNetworkManager();

    std::string post(const std::string& path, const std::map<std::string, std::string>& params);
    std::string get(const std::string& path);
    std::string del(const std::string& path);

private:
    std::string serverUrl;
};

#endif