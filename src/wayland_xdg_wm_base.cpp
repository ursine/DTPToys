//
// Created by bear on 3/29/20.
//

#include "wayland_xdg_wm_base.h"


static void WL::xdg_wm_base_ping(void* data, struct xdg_wm_base *shell, uint32_t serial)
{
    auto xdg = static_cast<WL::WaylandXdgWmBase*>(data);
    xdg->logger->info("Got a ping, serial {}", serial);
    xdg_wm_base_pong(shell, serial);
}

static const struct xdg_wm_base_listener xdg_wm_base_listener = {
    WL::xdg_wm_base_ping,
};


WL::WaylandXdgWmBase::WaylandXdgWmBase(wl_registry* reg, uint32_t id, uint32_t version):
    registry(reg),
    wm_base(static_cast<xdg_wm_base*>(wl_registry_bind(registry, id, &xdg_wm_base_interface, 1)))
{
    logger = GC::log_get("xdg");
    xdg_wm_base_add_listener(wm_base, &xdg_wm_base_listener, this);
}
