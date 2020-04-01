//
// Created by bear on 3/29/20.
//

#include "xdg-shell-client-protocol.h"
#include "window.h"
#include <utility>

static void
handle_xdg_surface_configure(void *data, struct xdg_surface *surface,
                             uint32_t serial)
{
    auto window = static_cast<WL::Window*>(data);

    xdg_surface_ack_configure(surface, serial);

    if (window->wait_for_configure) {
        redraw(window, NULL, 0);
        window->wait_for_configure = false;
    }
}

static const struct xdg_surface_listener xdg_surface_listener = {
        handle_xdg_surface_configure,
};

WL::Window::Window(std::shared_ptr<WL::Display> display, int width, int height) :
    display(std::move(display)),
    surface(display->get_compositor()->get_surface()),
    local_xdg_surface(xdg_wm_base_get_xdg_surface(display->get_base()->get_base(), surface)),
    local_xdg_toplevel(nullptr),
    prev_buffer(nullptr),
    callback(nullptr),
    width(width),
    height(height), wait_for_configure(true)
{
    xdg_surface_add_listener(local_xdg_surface, &xdg_surface_listener, this);

    window->xdg_toplevel =
            xdg_surface_get_toplevel(window->xdg_surface);
    assert(window->xdg_toplevel);
    xdg_toplevel_add_listener(window->xdg_toplevel,
                              &xdg_toplevel_listener, window);

    xdg_toplevel_set_title(window->xdg_toplevel, "simple-shm");
    wl_surface_commit(window->surface);
    window->wait_for_configure = true;

}
