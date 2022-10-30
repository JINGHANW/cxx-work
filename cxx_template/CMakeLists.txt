cmake_minimum_required(VERSION 3.23)
project(cxx_template)

set(CMAKE_CXX_STANDARD 11)

add_executable(cxx_template main.cpp NLcomponent.cpp NLcomponent.h Graphic.cpp Graphic.h TextBook.cpp TextBook.h)
