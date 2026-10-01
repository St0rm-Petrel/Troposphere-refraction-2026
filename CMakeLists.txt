cmake_minimum_required(VERSION 3.16)
project(RefractionModel CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(refraction_app
    main.cpp
    Models.cpp
)