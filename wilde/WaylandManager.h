//
// Created by bear on 5/3/20.
//

#pragma once

#include <stdexcept>
#include <fmt/format.h>
#include <wayland-client.h>
#include <spdlog/spdlog.h>

template<typename T>
void null_deleter(T*) {}

template<typename T>
std::shared_ptr<T> make_immortal_shared(T* const to_share) {
  return std::shared_ptr<T>(to_share, null_deleter<T>);
}

namespace wl {

// Exceptions
class WLBaseException : public std::runtime_error {
public:
  explicit WLBaseException(const std::string& s) : std::runtime_error(s) {}
};

class DisplayNotConnected : public WLBaseException {
public:
  explicit DisplayNotConnected()
    :WLBaseException("Unable to connect to display") {}
};

class UnableToBind : public WLBaseException {
public:
  explicit UnableToBind(const wl_interface* const ifc)
      :WLBaseException(fmt::format("unable to bind {}", ifc->name)) {}
};

class FailedToInstance : public WLBaseException {
public:
  explicit FailedToInstance(const std::string& obj)
    :WLBaseException(fmt::format("Failed to instance {}", obj)) {}
};

// Forward Dcl's
class WaylandManager;
class Compositor;
class Shell;
class Surface;
class ShellSurface;

// Utilities
template<typename T>
class Bindable {
protected:
  WaylandManager* const wm;
  T* bound;
public:
  Bindable(WaylandManager* mgr, wl_registry* registry, uint32_t name, uint32_t version,
           const wl_interface* const interface)
      :wm { mgr },
       bound { static_cast<T*>(wl_registry_bind(registry, name, interface, version)) }
  {
    // If it couldn't bind, throw an exception
    if (bound == nullptr) {
      throw UnableToBind(interface);
    }
  }
  ~Bindable() = default;
};

class WaylandManager {
private:
  std::shared_ptr<Compositor> compositor;
  std::shared_ptr<Shell> shell;

  std::shared_ptr<wl_display> display;
  std::shared_ptr<wl_registry> registry;
  std::shared_ptr<wl_shm> wl_shm;

public:
  WaylandManager();
  ~WaylandManager() {
    shell.reset();
    compositor.reset();
  }

  void add_compositor(wl_registry* registry, uint32_t name, uint32_t version);
  void add_shell(wl_registry* registry, uint32_t name, uint32_t version);

  void run() {
    while (wl_display_dispatch(display.get()) != -1) {
    }
  }

private:
  static void registry_add_object (void* data, wl_registry* registry,
    uint32_t name, const char* interface, uint32_t version);
  static void registry_remove_object (void* data, wl_registry* registry,
    uint32_t name);
};

class Compositor : public Bindable<wl_compositor> {
public:
  Compositor(WaylandManager* mgr, wl_registry* registry, uint32_t name, uint32_t version);
  ~Compositor() {
    wl_compositor_destroy(bound);
  }

  std::shared_ptr<wl_surface> create_surface() {
    wl_surface* const surface = wl_compositor_create_surface(bound);
    if (surface == nullptr) {
      throw FailedToInstance("surface");
    }
    return make_immortal_shared(surface);
  }
};


class ShellSurface {
protected:
  std::shared_ptr<wl_shell_surface> shell_surface;

public:
  ShellSurface(wl_surface* shell, wl_compositor* cmp) {

  }
};


class Shell : public Bindable<wl_shell> {
public:
  Shell(WaylandManager* mgr, wl_registry *registry, uint32_t name, uint32_t version);
  ~Shell() = default;

  wl_shell_surface* get_shell_surface(wl_surface* sfc) {
    auto shell_surface = wl_shell_get_shell_surface(bound, sfc);
    if (shell_surface == nullptr) {
      throw FailedToInstance("shell_surface");
    }
    return shell_surface;
  }
};

};