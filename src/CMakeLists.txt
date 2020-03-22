include_directories(.)

add_executable(DTPToys
        LibCore/Object.cpp
        LibCore/EventLoop.cpp
        LibCore/Event.cpp
        main.cpp
        wayland_display.cpp
        wayland_display.h
        wayland_registry.cpp
        wayland_registry.h)

target_link_libraries(DTPToys PRIVATE ${WAYLAND_LIBRARIES} spdlog)
