cmake_minimum_required(VERSION 2.8)

project(Logger)

set(SOURCE_DIR "src")
set(Logger_VERSION_MAJOR 2)
set(Logger_VERSION_MINOR 1)
set(Logger_VERSION_PATCH 0)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

add_library(Logger SHARED ${SOURCE_DIR}/Logger.cpp)
SET_TARGET_PROPERTIES(Logger PROPERTIES VERSION ${Logger_VERSION_MAJOR}.${Logger_VERSION_MINOR}.${Logger_VERSION_PATCH})

INSTALL(FILES ${SOURCE_DIR}/Logger.hpp DESTINATION include/Logger)
INSTALL(TARGETS Logger DESTINATION lib EXPORT FindLogger)
INSTALL(EXPORT FindLogger DESTINATION share/Logger)
