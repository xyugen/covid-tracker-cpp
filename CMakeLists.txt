cmake_minimum_required(VERSION 3.10)
project(CovidTracker)

find_package(CURL REQUIRED)

add_executable(CovidTracker main.cpp)

target_link_libraries(CovidTracker CURL::libcurl)
