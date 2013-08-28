cmake_minimum_required(VERSION 2.8)

project(Logger)

set(SOURCE_DIR "src")

add_library(Logger SHARED ${SOURCE_DIR}/Logger.cpp)


