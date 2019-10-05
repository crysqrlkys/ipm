cmake_minimum_required(VERSION 3.15)
project(des)

set(CMAKE_CXX_STANDARD 14)

add_executable(des main.cpp constants.h DES.cpp DES.h utils.cpp utils.h DES2.cpp DES2.h DES3.cpp DES3.h)