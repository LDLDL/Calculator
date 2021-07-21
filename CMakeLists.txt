cmake_minimum_required(VERSION 3.17)
project(Calculator)

set(CMAKE_CXX_STANDARD 11)

add_executable(Calculator main.cpp dfa.cpp dfa.h grammar.cpp grammar.h grammar_lr1.cpp grammar_lr1.h)