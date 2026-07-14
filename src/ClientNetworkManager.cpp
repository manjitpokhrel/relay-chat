#include "ClientNetworkManager.h"
#include <iostream>

ClientNetworkManager::ClientNetworkManager(
    const std::string& baseUrl)
    : baseUrl(baseUrl),
      client(std::make_unique<httplib::Client>(
          baseUrl.c_str())) {
    client->set_connection_timeout(5);
    client->set_read_timeout(5);
}

std::string ClientNetworkManager::post(
    const std::string& path,
    const httplib::Params& params) {
    auto res = client->Post(
        path.c_str(), params);
    if (res && res->status == 200)
        return res->body;
    return "{}";
}

std::string ClientNetworkManager::get(
    const std::string& path) {
    auto res = client->Get(path.c_str());
    if (res && res->status == 200)
        return res->body;
    return "[]";
}

std::string ClientNetworkManager::del(
    const std::string& path) {
    auto res = client->Delete(path.c_str());
    if (res && res->status == 200)
        return res->body;
    return "{}";
}

bool ClientNetworkManager::isConfigured() const {
    return !baseUrl.empty();
}

std::string ClientNetworkManager::getBaseUrl() const {
    return baseUrl;
}