cmake_minimum_required(VERSION 3.20)
project(BigInteger)

set(CMAKE_CXX_STANDARD 20)

add_executable(BigInteger main.cpp BigInt.cpp BigInt.h)
