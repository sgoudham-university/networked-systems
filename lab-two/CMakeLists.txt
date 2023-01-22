cmake_minimum_required(VERSION 3.24)
set(CMAKE_C_STANDARD 23)

project(lab-two C)

add_executable(http_connect)
target_sources(http_connect PRIVATE ../lib/util.c ../lib/util.h src/http_connect.c)
install(TARGETS http_connect)