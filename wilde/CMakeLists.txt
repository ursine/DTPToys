cmake_minimum_required(VERSION 3.1...3.16)

project(wilde VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(DEFAULT_BUILD_TYPE "Debug")
set(Boost_USE_MULTITHREADED ON)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(FindPkgConfig)
include(FeatureSummary)
include(GNUInstallDirs)

#find_package(Wayland REQUIRED)
find_package(spdlog REQUIRED)
find_package(Boost REQUIRED COMPONENTS regex date_time system filesystem thread graph program_options)


#include_directories(${WAYLAND_CLIENT_INCLUDE_DIR})

#add_subdirectory(src)

add_executable(wilde main.cc)

if(Boost_FOUND)
    include_directories(${BOOST_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    add_definitions(${Boost_DEFINITIONS})

    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(wilde ${Boost_LIBRARIES})
endif()
