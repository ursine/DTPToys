//
// Created by bear on 3/22/20.
//

#pragma once

#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include <memory>


namespace WL {

    class WaylandSeat {
    private:
        wl_registry* const registry;

    protected:
        wl_seat* const seat;

    public:
        explicit WaylandSeat(wl_registry* reg, int id);

    };
}
