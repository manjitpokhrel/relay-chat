#ifndef CLIENTNETWORKMANAGER_H
#define CLIENTNETWORKMANAGER_H

#include "httplib.h"
#include <string>
#include <memory>

class ClientNetworkManager {
private:
    std::string baseUrl;
    std::unique_ptr<httplib::Client> client;

public:
    explicit ClientNetworkManager(
        const std::string& baseUrl);

    std::string post(
        const std::string& path,
        const httplib::Params& params);

    std::string get(
        const std::string& path);

    std::string del(
        const std::string& path);

    bool isConfigured() const;
    std::string getBaseUrl() const;
};

#endif