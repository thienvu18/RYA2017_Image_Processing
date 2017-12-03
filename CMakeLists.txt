cmake_minimum_required(VERSION 3.8)
project(RYA_Video_Processing)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)

set(SOURCE_FILES TCPClient.cpp main.cpp)
add_executable(RYA_Video_Processing ${SOURCE_FILES})
target_link_libraries(RYA_Video_Processing ${OpenCV_LIBS})