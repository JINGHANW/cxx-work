cmake_minimum_required(VERSION 3.21)
project(libevent_c C)

set(CMAKE_C_STANDARD 11)
include_directories(/usr/local/include)
link_libraries(/usr/local/lib
        /usr/lib)

find_package(Libevent REQUIRED)
add_executable(libevent_c main.c)
target_link_libraries(libevent_c libevent::core)
