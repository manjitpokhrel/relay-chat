#include "RemoteDataService.h"

RemoteDataService::RemoteDataService(
    const std::string& serverUrl)
    : network(std::make_unique<ClientNetworkManager>(
        serverUrl)),
      serverUrl(serverUrl) {}