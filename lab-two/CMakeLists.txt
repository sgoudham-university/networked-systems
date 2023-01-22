cmake_minimum_required(VERSION 3.24)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/dist")

project(lab-two C)

add_executable(http_connect)
target_sources(http_connect PRIVATE src/util.c src/util.h src/http_connect.c)
install(TARGETS http_connect)