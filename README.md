# Relay Chat

> A lightweight desktop chat application built with **C++17**, **Qt6**, and **SQLite**, demonstrating clean Object-Oriented Design principles through a decoupled 4-layer architecture.

[RELAY_PROPOSAL.docx](https://github.com/user-attachments/files/28667576/RELAY_PROPOSAL.docx)

## Overview

**Relay** is a lightweight, local-prototype desktop chat application developed using **C++17**, the **Qt6 Framework**, and **SQLite**.

The project is designed around a clean **4-layer architecture** that demonstrates core **Object-Oriented Programming (OOP)** principles while maintaining strict separation of concerns. The architecture ensures that the graphical user interface remains completely decoupled from data persistence and business logic.

Currently, Relay functions as a fully operational local prototype where multiple users can:

* Register and log into the application
* Create and join chat rooms
* Exchange messages in real time
* Persist conversations and user data through SQLite storage

---

## Project Team

| Member      | Responsibility                                 |
| ----------- | ---------------------------------------------- |
| **Manjit**  | Controller Development, Team Lead, Integration |
| **Deepika** | Database Layer                                 |
| **Yubik**   | Core Models & OOP Design                       |
| **Adyut**   | GUI Layer                                      |
| **Prasun**  | Testing & Documentation                        |

---

## Git Workflow

### Branch Structure

```text
main
├── dev                 
├── feature/database  
├── feature/models      
├── feature/gui         
└── feature/testing     
```

### Workflow

1. Developers work on their dedicated feature branches.
2. Completed features are merged into the `dev` branch.
3. Integration testing is performed on `dev`.
4. Stable releases are promoted to the `main` branch.

---

## Features

### User Authentication

* User registration
* Secure login functionality

### Room Management

* Create chat rooms
* Join existing chat rooms

### Real-Time Messaging

* Live chat communication
* Automatic 2-second polling refresh mechanism

### Chat Utilities

* Clear local chat view history

### Data Persistence

* User accounts stored in SQLite
* Messages retained across application restarts

---

# System Architecture

Relay follows a strict layered architecture that separates presentation, application logic, abstraction, and data persistence.

```text
┌────────────────────────────────────────────┐
│                 GUI Layer                  │
│              (Qt Widgets UI)               │
└───────────────────┬────────────────────────┘
                    │
                    ▼
┌────────────────────────────────────────────┐
│               AppController                │
│ Coordinates UI Flow & Business Logic       │
└───────────────────┬────────────────────────┘
                    │
                    ▼
┌────────────────────────────────────────────┐
│               IDataService                 │
│      Abstract Interface / Dependency       │
└───────────────────┬────────────────────────┘
                    │
                    ▼
┌────────────────────────────────────────────┐
│             LocalDataService               │
│       SQLite Database Implementation       │
└────────────────────────────────────────────┘
```

---

## Architectural Design Rules

### Separation of Concerns

The GUI layer is responsible only for:

* Widget rendering
* User interaction capture

All business actions are delegated to the `AppController`.

### Dependency Inversion

The `AppController` depends solely on the abstract:

```cpp
IDataService
```

and remains independent of database implementation details.

### Extensibility

The application is designed for future migration to cloud infrastructure.

Transitioning from:

```cpp
LocalDataService
```

to

```cpp
RemoteDataService
```

(e.g., AWS RDS-backed implementation) requires only a single instantiation change in `main.cpp`.

---

# Object-Oriented Programming Implementation

Relay demonstrates multiple OOP concepts to maintain clean abstractions and scalable architecture.

## Abstract Classes

* `BaseEntity`
* `IDataService`

These define common behaviors and contracts across the system.

---

## Inheritance

The following models inherit from `BaseEntity`:

* `User`
* `Room`
* `Message`

This provides shared metadata and reusable functionality.

---

## Polymorphism

Runtime polymorphism is achieved through method overriding, particularly:

```cpp
toString()
```

which is implemented differently by each derived model.

---

## Encapsulation

Model attributes are declared as:

```cpp
private
```

or

```cpp
protected
```

and accessed through controlled public getters and setters.

---

## Composition

A `Room` object owns and manages collections of:

```cpp
Message
```

objects, establishing a composition relationship.

---

## Smart Pointers

Memory management avoids raw pointers by using:

```cpp
std::unique_ptr
std::shared_ptr
```

to ensure safe ownership and automatic cleanup.

---

## RAII (Resource Acquisition Is Initialization)

Managed through:

```cpp
DatabaseManager
```

which automatically handles:

* Database connections
* Transactions
* File resources

through constructor and destructor lifecycles.

---

## Dependency Injection

The `AppController` receives its required data service through constructor injection:

```cpp
AppController(std::shared_ptr<IDataService> service)
```

This removes hardcoded dependencies and improves testability.

---

# Technology Stack

| Component       | Technology             |
| --------------- | ---------------------- |
| Language        | C++17                  |
| UI Framework    | Qt 6.11.0 (Qt Widgets) |
| Database        | SQLite                 |
| Build System    | CMake                  |
| Version Control | Git & GitHub           |

---

# Setup & Installation

## Prerequisites

Ensure the following tools are installed:

* C++17 compatible compiler (GCC, Clang, or MSVC)
* CMake 3.16+
* Qt 6.11.0 SDK
* SQLite3 Development Libraries

---

## Clone the Repository

```bash
git clone https://github.com/<your-organization>/relay.git
cd relay
```

---

## Build the Project

```bash
mkdir build
cd build

cmake ..
cmake --build .
```

---

## Run the Application

```bash
./Relay
```

> Executable name may vary depending on your operating system and build configuration.

---

# Project Structure

```text
relay/
│
├── CMakeLists.txt
│   └── Main CMake build configuration
│
├── README.md
│   └── Project overview and documentation
│
├── src/
│   │
│   ├── main.cpp
│   │   └── Dependency Injection wiring & application entry point
│   │
│   ├── controller/
│   │   └── AppController orchestration logic
│   │
│   ├── models/
│   │   └── Core OOP Models
│   │       • BaseEntity
│   │       • User
│   │       • Room
│   │       • Message
│   │
│   ├── view/
│   │   └── Qt Widgets GUI layer
│   │
│   └── service/
│       └── IDataService abstraction
│       └── SQLite implementation
│
└── docs/
    └── Documentation
    └── Test Plans
    └── Checklists
    └── Logs
```

---

# Future Enhancements

* Cloud-based database integration
* Multi-device synchronization
* Secure password hashing & authentication upgrades
* Networked real-time communication
* User presence indicators
* File and media sharing
* Notification system

---

# License

This project is developed as an academic software engineering project and serves as a demonstration of OOP principles, layered architecture, and modern C++ application design.

