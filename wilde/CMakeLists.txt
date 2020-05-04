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
include(CheckSymbolExists)

find_package(spdlog REQUIRED)
find_package(Boost REQUIRED COMPONENTS regex date_time system filesystem thread graph program_options)

check_symbol_exists("posix_fallocate" "fcntl.h" HAVE_POSIX_FALLOCATE)
check_symbol_exists("__NR_memfd_create" "sys/syscall.h" HAVE_MEMFD_CREATE)

#include_directories(${WAYLAND_CLIENT_INCLUDE_DIR})

#add_subdirectory(src)
pkg_check_modules(Wayland_Client REQUIRED wayland-client)


add_executable(wilde main.cc fontinformation.cc fontinformation.h globalutils.h
        systemdetails.cc systemdetails.h WaylandManager.cc WaylandManager.h)

if(Boost_FOUND)
    include_directories(${BOOST_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    add_definitions(${Boost_DEFINITIONS})

    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(wilde ${Boost_LIBRARIES})
endif()

target_link_libraries(wilde ${Wayland_Client_LIBRARIES})