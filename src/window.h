//
// Created by bear on 3/29/20.
//

#pragma once

#include "xdg-shell-client-protocol.h"
#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include <memory>

#include "wayland_display.h"

struct buffer {
    struct wl_buffer *buffer;
    void *shm_data;
    int busy;
};

namespace WL {

    class Window {
    protected:
        std::shared_ptr<Display> display;

        wl_surface *surface;
        xdg_surface *local_xdg_surface;
        xdg_toplevel *local_xdg_toplevel;
        buffer buffers[2];
        buffer *prev_buffer;
        wl_callback *callback;

        int width;
        int height;

    public:
        bool wait_for_configure;

        Window(std::shared_ptr<WL::Display> d, int w, int h);
        ~Window() = default;
    };

};