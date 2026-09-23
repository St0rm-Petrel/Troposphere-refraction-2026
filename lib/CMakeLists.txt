project(lib VERSION 0.1 LANGUAGES CXX)

set(PROJECT_SOURCES
        water_vapour.cpp
        water_vapour.h
)

add_library(lib STATIC ${PROJECT_SOURCES})
