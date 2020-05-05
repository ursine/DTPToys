//
// Created by bear on 5/3/20.
//

#pragma once

#include <stdexcept>
#include <fmt/format.h>
#include <wayland-client.h>
#include <spdlog/spdlog.h>

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


// Utilities
template<typename T>
class Bindable {
protected:
  T* bound;
public:
  Bindable(wl_registry* registry, uint32_t name, uint32_t version,
           const wl_interface* const interface)
      :bound { static_cast<T*>(wl_registry_bind(registry, name, interface, version)) }
  {
    // If it couldn't bind, throw an exception
    if (bound == nullptr) {
      throw UnableToBind(interface);
    }
  }
  ~Bindable() = default;
};

class Compositor;
class Shell;

class WaylandManager {
private:
  std::shared_ptr<Compositor> compositor;
  std::shared_ptr<Shell> shell;

  std::shared_ptr<wl_display> display;
  std::shared_ptr<wl_registry> registry;
  std::shared_ptr<wl_surface> surface;
  std::shared_ptr<wl_shm> wl_shm;

public:
  WaylandManager();
  ~WaylandManager() = default;

  void add_compositor(wl_registry* registry, uint32_t name, uint32_t version);
  void add_shell(wl_registry* registry, uint32_t name, uint32_t version);

private:
  static void registry_add_object (void* data, wl_registry* registry,
    uint32_t name, const char* interface, uint32_t version);
  static void registry_remove_object (void* data, wl_registry* registry,
    uint32_t name);
};

class Compositor : public Bindable<wl_compositor> {
public:
  Compositor(wl_registry* registry, uint32_t name, uint32_t version);
  ~Compositor() = default;

  wl_surface* create_surface() {
    auto surface = wl_compositor_create_surface(bound);
    if (surface == nullptr) {
      fprintf(stderr, "Can't create surface\n");
      exit(1);
    } else {
      fprintf(stderr, "Created surface\n");
    }
  }
};

class Shell : public Bindable<wl_shell> {
public:
  Shell(wl_registry *registry, uint32_t name, uint32_t version);
  ~Shell() = default;
};

};