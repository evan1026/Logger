cmake_minimum_required(VERSION 2.8)

project(Logger)

set(SOURCE_DIR "src")

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

add_library(Logger SHARED ${SOURCE_DIR}/Logger.cpp)

INSTALL(FILES ${SOURCE_DIR}/Logger.hpp DESTINATION include/Logger)
INSTALL(TARGETS Logger DESTINATION lib EXPORT FindLogger)
INSTALL(EXPORT FindLogger DESTINATION share/Logger)
