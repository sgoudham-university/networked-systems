cmake_minimum_required(VERSION 3.24)
set(CMAKE_C_STANDARD 23)

project(lab-one C)

add_executable(hello_client)
add_executable(hello_server)
target_sources(hello_client PRIVATE ../lib/util.c ../lib/util.h src/hello_client.c)
target_sources(hello_server PRIVATE ../lib/util.c ../lib/util.h src/hello_server.c)
install(TARGETS hello_client hello_server)