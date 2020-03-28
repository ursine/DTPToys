//
// Created by bear on 3/28/20.
//

#pragma once

#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include <memory>

namespace WL {

    class WaylandCompositor {
    private:
        wl_registry* const registry;

    protected:
        wl_compositor* compositor = nullptr;

    public:
        WaylandCompositor(wl_registry* registry, uint32_t id, uint32_t version);
        ~WaylandCompositor();
    };

}