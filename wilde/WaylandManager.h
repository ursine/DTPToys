//
// Created by bear on 5/3/20.
//

#pragma once

#include <wayland-client.h>
#include <spdlog/spdlog.h>


class WaylandManager {
private:
  std::shared_ptr<wl_display> display;
  std::shared_ptr<wl_registry> registry;
  std::shared_ptr<wl_compositor> compositor;
  std::shared_ptr<wl_surface> surface;
  std::shared_ptr<wl_shell> shell;
  std::shared_ptr<wl_shm> wl_shm;

public:
  WaylandManager();

  void add_compositor(wl_registry* registry, uint32_t name, uint32_t version);
  void add_shell(wl_registry* registry, uint32_t name, uint32_t version);
};
