//
// Created by bear on 3/22/20.
//

#pragma once

#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include <memory>

#include "gc_logging_utils.h"

namespace WL {

    class WaylandSeat {
    private:
        wl_registry* const registry;

    protected:
        wl_seat* const seat;

        std::shared_ptr<spdlog::logger> logger;

    public:
        bool need_roundtrip;
        int32_t repeat_rate;
        int32_t repeat_delay;

    public:
        explicit WaylandSeat(wl_registry* registry, uint32_t id, uint32_t version);
        ~WaylandSeat();
    };

}
