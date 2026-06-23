#include "AppController.h"

// Service injected from outside.
// Controller never knows if it is SQLite or AWS.
AppController::AppController(
    std::unique_ptr<IDataService> service)
    : service(std::move(service)) {}