//
// Created by bear on 3/28/20.
//

#include "wayland_shm.h"

WL::WaylandShm::WaylandShm(wl_registry* registry, uint32_t id, uint32_t version) :
    registry(registry),
    shm(static_cast<wl_shm*>(wl_registry_bind(registry, id, &wl_shm_interface, version)))
{
}
