//
// Created by bear on 3/28/20.
//

#include "wayland_compositor.h"

WL::WaylandCompositor::WaylandCompositor(wl_registry* registry, uint32_t id, uint32_t version):
    registry(registry),
    compositor(static_cast<wl_compositor*>(wl_registry_bind(registry, id, &wl_compositor_interface, version)))
{
}

WL::WaylandCompositor::~WaylandCompositor()
{
    if (compositor!=nullptr) wl_compositor_destroy(compositor);
}

wl_surface* WL::WaylandCompositor::get_surface() {
    return wl_compositor_create_surface(compositor);
}
