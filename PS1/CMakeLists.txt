cmake_minimum_required(VERSION 3.7)
project(HoughTransform)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp Hough.cpp Hough.h ImageProcess.cpp ImageProcess.h)
add_executable(HoughTransform ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(HoughTransform ${OpenCV_LIBS})

