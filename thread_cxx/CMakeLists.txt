cmake_minimum_required(VERSION 3.22)
project(thread_cxx)

set(CMAKE_CXX_STANDARD 11)

add_executable(thread_cxx main.cpp)

target_link_libraries(thread_cxx -lpthread -luuid)