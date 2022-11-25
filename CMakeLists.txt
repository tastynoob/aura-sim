cmake_minimum_required(VERSION 3.0.0)
project(aura-sim VERSION 0.1.0)

file(GLOB_RECURSE SC_FILES src/*.cc)

add_executable(aura-sim src/main.cc ${SC_FILES})
include_directories(src)