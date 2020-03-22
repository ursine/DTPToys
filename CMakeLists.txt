cmake_minimum_required(VERSION 3.13)

project(DTPToys LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(FindPkgConfig)
include(FeatureSummary)
include(GNUInstallDirs)

find_package(Wayland REQUIRED)
find_package(spdlog REQUIRED)

include_directories(${WAYLAND_CLIENT_INCLUDE_DIR})

add_subdirectory(src)
