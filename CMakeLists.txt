cmake_minimum_required(VERSION 4.0)
project(memory_pool)

set(CMAKE_CXX_STANDARD 20)

add_executable(memory_pool src/main.cpp
        src/memory_pool.cpp
        include/memory_pool.h
        test/test_memory_pool.cpp
        test/tests.h)
