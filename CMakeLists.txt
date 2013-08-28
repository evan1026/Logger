cmake_minimum_required(VERSION 2.8)

project(Logger)

set(SOURCE_DIR "src")

add_library(Logger SHARED ${SOURCE_DIR}/Logger.cpp)

INSTALL(FILES ${SOURCE_DIR}/Logger.hpp DESTINATION include/Logger)
INSTALL(TARGETS Logger DESTINATION lib EXPORT FindLogger)
INSTALL(EXPORT FindLogger DESTINATION share/Logger)
