cmake_minimum_required(VERSION 3.13)

project(DTPToys LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Wayland REQUIRED)
include_directories(${WAYLAND_CLIENT_INCLUDE_DIR})

add_executable(DTPToys src/main.cpp src/wayland_display.cpp src/wayland_display.h src/wayland_registry.cpp src/wayland_registry.h)

target_link_libraries(DTPToys PRIVATE ${WAYLAND_LIBRARIES})