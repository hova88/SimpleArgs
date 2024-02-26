cmake_minimum_required(VERSION 3.11)
project(SimpleArgs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SOURCES
    utils/args.h
    utils/parser.h
)

add_compile_options($<$<CONFIG:Release>:-O2>)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Executable
add_executable(${PROJECT_NAME} main.cc)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_include_directories(${PROJECT_NAME} PRIVATE ./)

