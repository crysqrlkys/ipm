cmake_minimum_required(VERSION 3.15)
project(rsa)

set(CMAKE_CXX_STANDARD 14)

add_executable(rsa main.cpp RSA.cpp RSA.h utils.h utils.cpp)