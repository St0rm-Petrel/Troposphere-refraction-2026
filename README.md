# Qt + Boost + QCustomPlot Docker Development Template

A ready-to-use C++/Qt project template for students.  
It runs inside Docker and provides Qt, Qt Creator, Boost, CMake, and QCustomPlot.  
The example includes a small math library, a Qt GUI application, and Boost unit tests.

## Features

- Docker image with Qt, Qt Creator, Boost, CMake, and a C++ compiler
- Qt Widgets GUI application
- QCustomPlot integration for plotting
- Separate math core library with function calculating water vapour density
- Unit tests using Boost.Test
- X11 forwarding for GUI applications
- Windows support via Docker Desktop + VcXsrv
- Container creation scripts for Linux/macOS and Windows
- Project mounted from host into the container for live development

## Requirements

### Host system

- Docker Engine or Docker Desktop
- Docker Compose
- Git
- An X11 server:
  - Linux: Xorg
  - macOS: XQuartz
  - Windows: VcXsrv or Xming

### Inside the container

Everything needed for development is already installed in the Docker image:

- Qt
- Qt Creator
- Boost
- CMake
- Make / Ninja
- C++ compiler

## Quick Start

### 1. Clone the repository

    git clone <repository-url>
    cd <repository-directory>

### 2. Allow Docker to access your X11 server

#### Linux

    xhost +local:docker

If that does not work, try:

    xhost +local:root

#### macOS

Install and start XQuartz, then run:

    xhost + 127.0.0.1

#### Windows

Install VcXsrv, then start **XLaunch** with these settings:

- Multiple windows
- Start no client
- Clipboard
- Primary Selection
- Extra settings: check **Disable access control**

Make sure Windows Firewall allows VcXsrv.

### 3. Create and start the container

#### Linux / macOS

    ./create_container.sh

#### Windows

    create_container.bat

Or start it manually:

    docker compose up -d

Check running services:

    docker compose ps

### 4. Enter the container

    docker compose exec <service-name> bash

Replace `<service-name>` with the service name shown by `docker compose ps`.

You should see a prompt similar to:

    student@<container-id>:/app$

### 5. Build the project

Inside the container:

    cmake -S . -B build
    cmake --build build -j$(nproc)

If you prefer an in-source build:

    cmake .
    make -j$(nproc)

### 6. Run the tests

    ./build/test/test

### 7. Run the GUI application

    ./build/gui/gui

If the target name differs, check `gui/CMakeLists.txt`.

### 8. Open the project in Qt Creator

Inside the container:

    qtcreator &

## Project Structure

    .
    ├── CMakeLists.txt
    ├── Dockerfile
    ├── docker-compose.yml
    ├── create_container.sh
    ├── create_container.bat
    ├── QCustomPlot.cmake
    ├── gui/
    │   ├── CMakeLists.txt
    │   ├── main.cpp
    │   ├── mainwindow.cpp
    │   ├── mainwindow.h
    │   └── mainwindow.ui
    ├── lib/
    │   ├── CMakeLists.txt
    │   ├── water_vapour.cpp
    │   └── water_vapour.h
    └── test/
        ├── CMakeLists.txt
        ├── main.cpp
        └── water_vapour_test.cpp

### Directory overview

- `gui/` — Qt Widgets application and QCustomPlot usage
- `lib/` — reusable math/core library, e.g. water vapour density
- `test/` — Boost unit tests for the core library
- `Dockerfile` — image definition with Qt, Qt Creator, Boost, and build tools
- `docker-compose.yml` — container configuration and volume mounts
- `create_container.sh` / `create_container.bat` — helper scripts for container creation
- `QCustomPlot.cmake` — CMake helper for fetching/linking QCustomPlot

## Common Development Workflow

1. Edit files on the host machine.
2. The project directory is mounted into the container.
3. Rebuild inside the container.
4. Run tests or GUI.

## Adding New Code

When adding new source files, update the relevant `CMakeLists.txt`.

Typical places:

- New GUI files: `gui/CMakeLists.txt`
- New library files: `lib/CMakeLists.txt`
- New tests: `test/CMakeLists.txt`

After changing CMake files, reconfigure:

    cmake -S . -B build
    cmake --build build -j$(nproc)

## Notes for Students

- Keep the build directory out of version control.
- Run tests before submitting changes.
- Use the provided example as a starting point.
- Follow the existing CMake structure when adding new targets or files.
- GUI applications require a working X11 server.
