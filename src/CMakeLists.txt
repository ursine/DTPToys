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
#        LibCore/ConfigFile.cpp
#        LibCore/File.cpp
#        LibCore/Timer.cpp
#        LibCore/ElapsedTimer.cpp
#
#		LibGUI/Application.cpp
#		LibGUI/Action.cpp
#		LibGUI/Shortcut.cpp
#		LibGUI/Desktop.cpp
#		LibGUI/Label.cpp
#		LibGUI/Frame.cpp
#		LibGUI/Widget.cpp
#		LibGUI/Event.cpp
#		LibGUI/MenuBar.cpp
#		LibGUI/Window.cpp
#		LibGUI/Painter.cpp
#		LibGUI/TextBox.cpp
#		LibGUI/TextEditor.cpp
#		LibGUI/ScrollableWidget.cpp
#		LibGUI/Menu.cpp
#		LibGUI/MenuItem.cpp
#		LibGUI/AbstractButton.cpp
#		LibGUI/Button.cpp
#		LibGUI/ScrollBar.cpp
#		LibGUI/InputBox.cpp
#		LibGUI/Dialog.cpp
#		LibGUI/TextDocument.cpp
#		LibGUI/BoxLayout.cpp
#		LibGUI/Layout.cpp
#		LibGUI/CheckBox.cpp
#		LibGUI/UndoStack.cpp
#		LibGUI/Clipboard.cpp
#		LibGUI/SpinBox.cpp
#		LibGUI/SyntaxHighlighter.cpp
#		LibGUI/FontDatabase.cpp
#		LibGUI/RadioButton.cpp
#		LibGUI/Slider.cpp
#		LibGUI/GroupBox.cpp
#
#		LibGfx/Rect.cpp
#		LibGfx/Point.cpp
#		LibGfx/Size.cpp
#		LibGfx/StylePainter.cpp
#		LibGfx/Palette.cpp
#		LibGfx/Bitmap.cpp
#		LibGfx/Painter.cpp
#		LibGfx/Font.cpp
#		LibGfx/Emoji.cpp
#		LibGfx/Color.cpp
#		LibGfx/CharacterBitmap.cpp

		xdg-shell-protocol.c

        main.cpp

        wayland_display.cpp
        wayland_seat.cpp

        gc_logging_utils.h
        wayland_shm.cpp
        wayland_shm.h
        wayland_compositor.cpp
		wayland_xdg_wm_base.cpp
		wayland_xdg_wm_base.h wayland_utils.cpp wayland_utils.h window.cpp window.h)

target_link_libraries(DTPToys
        PRIVATE
        ${WAYLAND_LIBRARIES}
        ${SPDLOG_LIBRARIES})

target_include_directories(DTPToys PRIVATE ${CMAKE_CURRENT_BINARY_DIR})