cmake_minimum_required(VERSION 3.10)

project(usefulFuns VERSION 1.0)

set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(Eigen3 REQUIRED)

set(OpenCV_DIR /home/csl/Software/opencv-4.x/build)
find_package(OpenCV REQUIRED)

include_directories(
        ${EIGEN_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
)

add_executable(${CMAKE_PROJECT_NAME} src/super_pixel.cpp)

target_link_libraries(
        ${CMAKE_PROJECT_NAME} PRIVATE
        pthread
        ${OpenCV_LIBS}
)
