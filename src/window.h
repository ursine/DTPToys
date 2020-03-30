//
// Created by bear on 3/29/20.
//

#pragma once

#include "xdg-shell-client-protocol.h"
#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include "wayland_display.h"
#include <memory>


struct buffer {
    struct wl_buffer *buffer;
    void *shm_data;
    int busy;
};

namespace WL {

    class Window {
    protected:
        std::shared_ptr<Display> display;

        struct wl_surface *surface;
        struct xdg_surface *xdg_surface;
        struct xdg_toplevel *xdg_toplevel;
        struct buffer buffers[2];
        struct buffer *prev_buffer;
        struct wl_callback *callback;

        bool wait_for_configure;

        int width;
        int height;

    public:
        Window(std::shared_ptr<WL::Display> d, int w, int h);

        Window(const std::shared_ptr<WL::Display> &display, int width, int height);

        ~Window();
    };

};