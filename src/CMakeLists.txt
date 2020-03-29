add_custom_command(
        OUTPUT xdg-shell-client-protocol.h
        COMMAND ${WAYLAND_SCANNER_CMD} client-header ${WAYLAND_XDG_SHELL_XML} xdg-shell-client-protocol.h
)

add_custom_command(
        OUTPUT xdg-shell-protocol.c
        COMMAND ${WAYLAND_SCANNER_CMD} private-code ${WAYLAND_XDG_SHELL_XML} xdg-shell-protocol.c
)

add_executable(DTPToys
#        AK/JsonParser.cpp
#        AK/JsonValue.cpp
#        AK/LogStream.cpp
#        AK/MappedFile.cpp
#        AK/FileSystemPath.cpp
#        AK/SharedBuffer.cpp
#        AK/String.cpp
#        AK/StringImpl.cpp
#        AK/StringBuilder.cpp
#        AK/StringUtils.cpp
#        AK/StringView.cpp
#        AK/URL.cpp
#        AK/Utf8View.cpp
#
#        LibCore/Object.cpp
#        LibCore/EventLoop.cpp
#        LibCore/Event.cpp
#        LibCore/LocalServer.cpp
#        LibCore/IODevice.cpp
#        LibCore/Notifier.cpp
#        LibCore/LocalSocket.cpp
#        LibCore/Socket.cpp

		xdg-shell-protocol.c

        main.cpp

        wayland_display.cpp
        wayland_seat.cpp

        gc_logging_utils.h
        wayland_shm.cpp
        wayland_shm.h
        wayland_compositor.cpp
        WaylandXdgWmBase.cpp
		WaylandXdgWmBase.h)

target_link_libraries(DTPToys
        PRIVATE
        ${WAYLAND_LIBRARIES}
        ${SPDLOG_LIBRARIES})

target_include_directories(DTPToys PRIVATE ${CMAKE_CURRENT_BINARY_DIR})