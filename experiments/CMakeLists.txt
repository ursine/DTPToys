cmake_minimum_required(VERSION 3.15)

project(wilde LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(FindPkgConfig)
include(FeatureSummary)
include(GNUInstallDirs)

find_package(PkgConfig)
find_package(spdlog REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED)

pkg_check_modules(PKG_WAYLAND QUIET wayland-client++)
pkg_check_modules(PKG_WAYLAND_EXTRA QUIET wayland-client-extra++)
pkg_check_modules(EGL_REQUIRED egl)

include_directories(${PKG_WAYLAND_EXTRA_INCLUDE_DIR} ${PKG_WAYLAND_INCLUDE_DIR})

add_executable(wilde src/main.cc)

target_link_libraries(wilde PRIVATE
    ${PKG_WAYLAND_LIBRARIES} ${PKG_WAYLAND_EXTRA_LIBRARIES} ${SPDLOG_LIBRARIES})
