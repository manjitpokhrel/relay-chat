#include "ClientNetworkManager.h"

ClientNetworkManager::ClientNetworkManager(
    const std::string& baseUrl)
    : baseUrl(baseUrl) {}

std::string ClientNetworkManager::getBaseUrl() const {
    return baseUrl;
}

bool ClientNetworkManager::isConfigured() const {
    return !baseUrl.empty();
}