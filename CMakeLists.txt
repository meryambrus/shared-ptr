cmake_minimum_required(VERSION 3.29)
project(shared-prt)

set(CMAKE_CXX_STANDARD 17)

add_executable(shared-ptr main.cpp
        RefCounted.cpp
        RefCounted.h
        TestBase.cpp
        TestBase.h
        TestDerived.cpp
        TestDerived.h
        Tester.cpp
        Tester.h
        TestVariadic.cpp
        TestVariadic.h)
