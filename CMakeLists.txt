cmake_minimum_required(VERSION 3.24)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Werror")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/dist")

project(networked-systems C)

add_subdirectory(lab-one)
add_subdirectory(lab-two)