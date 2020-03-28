//
// Created by bear on 3/28/20.
//

#include "wayland_shm.h"
#include "gc_logging_utils.h"


static void shm_format(void* data, wl_shm* wl_shm, uint32_t format)
{
    auto waylandshm = static_cast<WL::WaylandShm*>(data);

    auto logger = GC::log_get("shm");

    logger->info("Supported graphical format {}", format);

    if (format == WL_SHM_FORMAT_XRGB8888) {}
    //    d->has_xrgb = true;
}

struct wl_shm_listener shm_listener = {
        shm_format
};



WL::WaylandShm::WaylandShm(wl_registry* registry, uint32_t id, uint32_t version) :
    registry(registry),
    shm(static_cast<wl_shm*>(wl_registry_bind(registry, id, &wl_shm_interface, version)))
{
    wl_shm_add_listener(shm, &shm_listener, this);
}

WL::WaylandShm::~WaylandShm() {
    wl_shm_destroy(shm);
}
