//
// Created by bear on 3/29/20.
//

#pragma once


#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include <memory>

#include "xdg-shell-client-protocol.h"

#include "gc_logging_utils.h"


namespace WL {

    class WaylandXdgWmBase {

        friend void xdg_wm_base_ping(void* data, struct xdg_wm_base *shell, uint32_t serial);

    private:
        wl_registry *const registry;
        std::shared_ptr<spdlog::logger> logger;

    protected:
        xdg_wm_base *wm_base;

    public:
        explicit WaylandXdgWmBase(wl_registry* reg, uint32_t id, uint32_t version);

    };

};
