cmake_minimum_required(VERSION 3.10)

project(usefulFuns VERSION 1.0)

set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/listfiles.cpp)

