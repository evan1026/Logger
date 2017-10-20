CXX ?= g++

build:
	${CXX} -std=c++11 Logger.cpp test.cpp -o test.out
