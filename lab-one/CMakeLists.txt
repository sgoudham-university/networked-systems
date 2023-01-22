cmake_minimum_required(VERSION 3.24)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/dist")

project(lab-one C)

add_executable(client)
add_executable(server)
target_sources(client PRIVATE src/util.c src/util.h src/client.c)
target_sources(server PRIVATE src/util.c src/util.h src/server.c)
install(TARGETS client server)