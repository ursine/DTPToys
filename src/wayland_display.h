//
// Created by bear on 3/18/20.
//

#pragma once

#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "wayland_seat.h"
#include "wayland_shm.h"
#include "wayland_compositor.h"
#include "wayland_xdg_wm_base.h"
#include "window.h"


namespace WL {

    static void global_registry_handler(void* data, wl_registry* registry,
                                        uint32_t id, const char* interface, uint32_t version);

    class Display {

        friend void global_registry_handler(void* data, wl_registry* registry,
           uint32_t id, const char* interface, uint32_t version);

    private:
        // Raw data type pointers
        wl_display* display = nullptr;

        std::shared_ptr<wl_registry> registry;

        std::shared_ptr<WL::WaylandSeat>        seat;
        std::shared_ptr<WL::WaylandShm>         shared_memory;
        std::shared_ptr<WL::WaylandCompositor>  compositor;
        std::shared_ptr<WL::WaylandXdgWmBase>   wm_base;

        std::shared_ptr<spdlog::logger> logger;

    public:
        Display();
        ~Display();

        int dispatch() { return wl_display_dispatch(display); }
        int roundtrip() {
            logger->info("Requesting roundtrip");
            return wl_display_roundtrip(display);
        }

        [[nodiscard]]
        int get_fd() const { return wl_display_get_fd(display); }

        [[nodiscard]]
        int flush() const { return wl_display_flush(display); }

        wl_display* get_ptr() { return display; }


    };

}
