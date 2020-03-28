//
// Created by bear on 3/22/20.
//

#include "wayland_seat.h"
#include <linux/input-event-codes.h>


static void pointer_enter(void *data, struct wl_pointer *wl_pointer, uint32_t serial,
                          struct wl_surface *surface, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    auto seat = static_cast<WL::WaylandSeat*>(data);

}

static void pointer_leave(void *data,
                          struct wl_pointer *wl_pointer,
                          uint32_t serial,
                          struct wl_surface *surface)
{
    auto seat = static_cast<WL::WaylandSeat*>(data);
}

static void pointer_motion(void *data,
                           struct wl_pointer *wl_pointer,
                           uint32_t time,
                           wl_fixed_t surface_x,
                           wl_fixed_t surface_y) {}

static void pointer_axis(void *data,
                         struct wl_pointer *wl_pointer,
                         uint32_t time,
                         uint32_t axis,
                         wl_fixed_t value) {}

static void pointer_frame(void *data,
                          struct wl_pointer *wl_pointer) {}

static void pointer_axis_source(void *data,
                                struct wl_pointer *wl_pointer,
                                uint32_t axis_source) {}

static void pointer_axis_stop(void *data,
                              struct wl_pointer *wl_pointer,
                              uint32_t time,
                              uint32_t axis) {}

static void pointer_axis_discrete(void *data,
                                  struct wl_pointer *wl_pointer,
                                  uint32_t axis,
                                  int32_t discrete)
{
    auto seat = static_cast<WL::WaylandSeat*>(data);
}

static void pointer_handle_button(void *data, struct wl_pointer *pointer,
                                  uint32_t serial, uint32_t time, uint32_t button, uint32_t state) {
    auto seat = static_cast<wl_seat*>(data);

    if (button == BTN_LEFT && state == WL_POINTER_BUTTON_STATE_PRESSED) {
        //xdg_toplevel_move(xdg_toplevel, seat, serial);
    }
}

static const struct wl_pointer_listener pointer_listener = {
        .enter = pointer_enter,
        .leave = pointer_leave,
        .motion = pointer_motion,
        .button = pointer_handle_button,
        .axis = pointer_axis,
        .frame = pointer_frame,
        .axis_source = pointer_axis_source,
        .axis_stop  = pointer_axis_stop,
        .axis_discrete = pointer_axis_discrete,
};



static void seat_handle_capabilities(void *data, struct wl_seat *seat, uint32_t capabilities)
{
    if (capabilities & WL_SEAT_CAPABILITY_POINTER) {
        wl_pointer* const pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(pointer, &pointer_listener, seat);
    }
}


static const struct wl_seat_listener seat_listener = {
        .capabilities = seat_handle_capabilities,
};

WL::WaylandSeat::WaylandSeat(wl_registry* reg, uint32_t id, uint32_t version):
        registry(reg),
        seat(static_cast<wl_seat*>(wl_registry_bind(registry, id, &wl_seat_interface, version)))
{
    wl_seat_add_listener(seat, &seat_listener, this);
}
