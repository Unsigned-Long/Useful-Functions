cmake_minimum_required(VERSION 3.10)

project(usefulFuns VERSION 1.0)

set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_STANDARD 17)

add_executable(usefulFuns ./src_funs/filesInDir.cpp)