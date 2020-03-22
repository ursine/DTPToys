
add_executable(DTPToys
        main.cpp
        wayland_display.cpp
        wayland_display.h
        wayland_registry.cpp
        wayland_registry.h)

target_link_libraries(DTPToys PRIVATE ${WAYLAND_LIBRARIES} spdlog)
