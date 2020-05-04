//
// Created by bear on 5/3/20.
//

#include "WaylandManager.h"

static void registry_add_object (void *data, struct wl_registry *registry,
  uint32_t name, const char *interface, uint32_t version)
{
  auto wm = static_cast<WaylandManager*>(data);
  std::string iface(interface);

  spdlog::info("Adding {} - {}", iface, version);

  if (iface==wl_compositor_interface.name) {
    wm->add_compositor(registry, name, version);
  }

  if (iface==wl_shell_interface.name) {
    wm->add_shell(registry, name, version);
  }

  /*
  else if (!strcmp(interface,"wl_shm")) {
    wl_shm = wl_registry_bind (registry, name, &wl_shm_interface, 1);
  }*/
}

static void registry_remove_object (void* data, wl_registry* registry,
  uint32_t name)
{
  spdlog::info("Removing {}", name);
}

WaylandManager::WaylandManager():
  display(wl_display_connect (nullptr), wl_display_disconnect)
{
  registry.reset(
      wl_display_get_registry(display.get()),
      wl_registry_destroy);

  wl_registry_listener registry_listener {
      &registry_add_object,
      &registry_remove_object
  };

  int res;
  res = wl_registry_add_listener(registry.get(), &registry_listener, this);
  res = wl_display_roundtrip(display.get());
  res = wl_display_roundtrip(display.get());

  surface.reset(wl_compositor_create_surface(compositor.get()));

  if (surface == nullptr) {
    fprintf(stderr, "Can't create surface\n");
    exit(1);
  } else {
    fprintf(stderr, "Created surface\n");
  }
}

void WaylandManager::add_compositor(wl_registry *registry, uint32_t name,
                                    uint32_t version)
{
  spdlog::info("Compositor added");
  compositor.reset(
    static_cast<wl_compositor*>(wl_registry_bind(registry, name, &wl_compositor_interface, version)),
    wl_compositor_destroy);
}

void WaylandManager::add_shell(wl_registry *registry, uint32_t name,
                               uint32_t version)
{
  spdlog::info("Shell added");
  shell.reset(
    static_cast<wl_shell*>(wl_registry_bind(registry, name, &wl_shell_interface, version)),
    wl_shell_destroy);
}
