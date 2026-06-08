#ifndef CLIENTNETWORKMANAGER_H
#define CLIENTNETWORKMANAGER_H

#include <string>

// Handles HTTP communication with backend server.
// Stub for now. Real implementation comes when
// we move to multi-device with AWS backend.
class ClientNetworkManager {
private:
    std::string baseUrl;

public:
    explicit ClientNetworkManager(
        const std::string& baseUrl);

    std::string getBaseUrl() const;
    bool isConfigured() const;
};

#endif