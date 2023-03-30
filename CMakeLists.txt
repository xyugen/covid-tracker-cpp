cmake_minimum_required(VERSION 3.10)
project(CovidTracker)

set(SOURCE main.cpp)

find_package(CURL REQUIRED)

add_executable(CovidTracker main.cpp)

if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
    target_link_libraries(CovidTracker ${CURL_LIBRARIES})
endif()
