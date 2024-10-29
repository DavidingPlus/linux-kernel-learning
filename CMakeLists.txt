cmake_minimum_required (VERSION 3.12)

project ("GNU C")

# 因为是测试 GNU C，因此就不指定 C/C++ 语言的版本了。


message ("-- Building on Linux ...")

# configure compiler gcc with Ccache
set (CMAKE_C_COMPILER "gcc")
set (CMAKE_CXX_COMPILER "g++")

message ("-- Using C Compiler: ${CMAKE_C_COMPILER} (${CMAKE_C_COMPILER_VERSION})")
message ("-- Using C++ Compiler: ${CMAKE_CXX_COMPILER} (${CMAKE_CXX_COMPILER_VERSION})")


add_subdirectory ("snippet")
