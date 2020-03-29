//
// Created by bear on 3/18/20.
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>

#include "wayland_shm.h"
#include "wayland_display.h"
#include "gc_logging_utils.h"

extern "C" {
    #include "xdg-shell-client-protocol.h"
}


static void WL::global_registry_handler(void* const data,
                                    wl_registry* const registry,
                                    uint32_t id,
                                    const char* const interface,
                                    uint32_t version)
{
    auto the_display = static_cast<WL::Display*>(data);
    auto logger = GC::log_get("registry");

    logger->info("Registry emitted {} version {} : id# {}", interface, version, id);

    if (strcmp(interface, wl_display_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_registry_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_callback_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_compositor_interface.name) == 0) {
        the_display->compositor = std::make_shared<WL::WaylandCompositor>(registry, id, 1);
        return;
    }

    if (strcmp(interface, wl_shm_pool_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_shm_interface.name) == 0) {
        the_display->shared_memory = std::make_shared<WL::WaylandShm>(registry, id, 1);
        return;
    }

    if (strcmp(interface, wl_buffer_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_data_offer_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_data_source_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_data_device_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_data_device_manager_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_shell_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_shell_surface_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_surface_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_seat_interface.name) == 0) {
        the_display->seat = std::make_shared<WL::WaylandSeat>(registry, id, 1);
        return;
    }

    if (strcmp(interface, wl_pointer_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_keyboard_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_touch_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_output_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_region_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, wl_subcompositor_interface.name) == 0) {
        return;
    }

    if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
        the_display->wm_base = std::make_shared<WL::WaylandXdgWmBase>(registry, id, 1);
        return;
    }
}

static void global_registry_remover(void *data,
                                    struct wl_registry *registry,
                                    uint32_t id)
{
    auto logger = GC::log_get("registry");
    auto the_display = static_cast<WL::Display*>(data);
    logger->info("Removing object from registry");
}

static const struct wl_registry_listener registry_listener = {
        WL::global_registry_handler,
        global_registry_remover
};

WL::Display::Display() {
    auto logger = GC::log_get("display");

    display = wl_display_connect(nullptr);

    if (display == nullptr) {
        logger->error("Can't connect to display");
        exit(EXIT_FAILURE);
    }
    logger->info("Connected to display");

    registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, this);

    dispatch();

    // Weston docs recommend two roundtrips
    roundtrip();
    roundtrip();
}

WL::Display::~Display() {
    auto logger = GC::log_get("display");

    // Delete the various objects
    compositor.reset();
    shared_memory.reset();
    seat.reset();

    wl_registry_destroy(registry);
    wl_display_flush(display);
    wl_display_disconnect(display);
    logger->info("Disconnected from display\n");
}


/*
wl_drm
wl_compositor id 2
wl_shm id 3
wl_output id 4
wl_output id 5
zxdg_output_manager_v1 id 6
wl_data_device_manager id 7
gtk_primary_selection_device_manager id 8
wl_subcompositor id 9
xdg_wm_base id 10
zxdg_shell_v6 id 11
wl_shell id 12
gtk_shell1 id 13
wp_viewporter id 14
zwp_pointer_gestures_v1 id 15
zwp_tablet_manager_v2 id 16
wl_seat id 17
zwp_relative_pointer_manager_v1 id 18
zwp_pointer_constraints_v1 id 19
zxdg_exporter_v1 id 20
zxdg_importer_v1 id 21
zwp_linux_dmabuf_v1 id 22
zwp_keyboard_shortcuts_inhibit_manager_v1 id 23
zwp_text_input_manager_v3 id 24
gtk_text_input_manager id 25
*/


