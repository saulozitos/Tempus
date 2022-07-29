cmake_minimum_required(VERSION 3.5)

project(Tempus LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(src ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME}
        ${src}/chronometer.cpp
        ${src}/date.cpp
        ${src}/datetime.cpp
        ${src}/main.cpp)
