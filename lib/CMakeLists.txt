project(lib VERSION 0.1 LANGUAGES CXX)

set(PROJECT_SOURCES
        water_vapour.cpp
        water_vapour.h
        atm_model.h
        exp_atm_model.cpp
        exp_atm_model.h
        seg_atm_model.cpp
        seg_atm_model.h
)

add_library(lib STATIC ${PROJECT_SOURCES})
