include_directories(.)

add_executable(DTPToys
        AK/JsonParser.cpp
        AK/JsonValue.cpp
        AK/LogStream.cpp
        AK/MappedFile.cpp
        AK/FileSystemPath.cpp
        AK/SharedBuffer.cpp
        AK/String.cpp
        AK/StringImpl.cpp
        AK/StringBuilder.cpp
        AK/StringUtils.cpp
        AK/StringView.cpp
        AK/URL.cpp
        AK/Utf8View.cpp

        LibCore/Object.cpp
        LibCore/EventLoop.cpp
        LibCore/Event.cpp
        LibCore/LocalServer.cpp
        LibCore/IODevice.cpp
        LibCore/Notifier.cpp
        LibCore/LocalSocket.cpp
        LibCore/Socket.cpp

        main.cpp
        wayland_display.cpp
        wayland_display.h wayland_seat.cpp wayland_seat.h)

target_link_libraries(DTPToys
        PRIVATE
        ${WAYLAND_LIBRARIES}
        ${SPDLOG_LIBRARIES})
