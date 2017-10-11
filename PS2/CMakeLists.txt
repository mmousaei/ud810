cmake_minimum_required(VERSION 3.7)
project(PS2)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
set(SOURCE_FILES main.cpp ImageProcess.cpp ImageProcess.h Disparity.cpp Disparity.h)
add_executable(PS2 ${SOURCE_FILES})


include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(PS2 ${OpenCV_LIBS})