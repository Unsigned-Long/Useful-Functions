cmake_minimum_required(VERSION 3.10)

project(usefulFuns VERSION 1.0)

find_package(fmt)

set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/sampling.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${FMT_INCLUDE_DIRS})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE fmt::fmt)