#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <random>
#include <sys/mman.h>

#include <spdlog/spdlog.h>
#include <wayland-client-protocol-extra.hpp>
#include <wayland-client.hpp>
#include <wayland-cursor.hpp>


// helper to create a std::function out of a member function and an object
template <typename R, typename T, typename... Args>
std::function<R(Args...)> bind_mem_fn(R(T::* func)(Args...), T *t)
{
  return [func, t] (Args... args)
  {
    return (t->*func)(args...);
  };
}

/*
static int new_memfd_region(char *unique_str) {
    char *shm;
    const int shm_size = 1024;
    int fd, ret;

    fd = memfd_create("Server memfd", MFD_ALLOW_SEALING);
    if (fd == -1)
        error("memfd_create()");

    ret = ftruncate(fd, shm_size);
    if (ret == -1)
        error("ftruncate()");

    ret = fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK);
    if (ret == -1)
        error("fcntl(F_SEAL_SHRINK)");

    shm = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm == MAP_FAILED)
        error("mmap()");

    sprintf(shm, "Secure zero-copy message from server: %s", unique_str);

    /* Seal writes too, but unmap our shared mappings beforehand
    ret = munmap(shm, shm_size);
    if (ret == -1)
    error("munmap()");
    ret = fcntl(fd, F_ADD_SEALS, F_SEAL_WRITE);
    if (ret == -1)
    error("fcntl(F_SEAL_WRITE)");

    ret = fcntl(fd, F_ADD_SEALS, F_SEAL_SEAL);
    if (ret == -1)
    error("fcntl(F_SEAL_SEAL)");

    return fd;
}
 */

// shared memory helper class
class shared_mem_t
{
private:
  std::string name;
  int fd = 0;
  size_t len = 0;
  void *mem = nullptr;

public:
  shared_mem_t() = default;
  shared_mem_t(const shared_mem_t&) = delete;
  shared_mem_t(shared_mem_t&&) noexcept = delete;
  shared_mem_t& operator=(const shared_mem_t&) = delete;
  shared_mem_t& operator=(shared_mem_t&&) noexcept = delete;

  explicit shared_mem_t(size_t size)
      : len(size)
  {
    // Very simple shared memory wrapper - do not use this in production code!
    // The generated memory regions are visible in the file system and can be
    // stolen by other running processes.
    // Linux code should use memfd_create when possible (ommited here for
    // simplicity).

    // create random filename
    std::stringstream ss;
    std::srand(std::time(nullptr));
    ss << '/' << std::rand();
    name = ss.str();

    // open shared memory file
    fd = shm_open(name.c_str(), O_RDWR | O_CREAT | O_EXCL, 0600);
    if(fd < 0)
      throw std::runtime_error("shm_open failed.");

    // set size
    if(ftruncate(fd, size) < 0)
      throw std::runtime_error("ftruncate failed.");

    // map memory
    mem = mmap(nullptr, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(mem == MAP_FAILED) // NOLINT
      throw std::runtime_error("mmap failed.");
  }

  ~shared_mem_t() noexcept
  {
    if(fd)
    {
      if(munmap(mem, len) < 0)
        std::cerr << "munmap failed.";
      if(close(fd) < 0)
        std::cerr << "close failed.";
      if(shm_unlink(name.c_str()) < 0)
        std::cerr << "shm_unlink failed";
    }
  }

  int get_fd() const
  {
    return fd;
  }

  void *get_mem()
  {
    return mem;
  }
};


int main(int argc, char* argv[]) {

  spdlog::info("Booting up");

  wayland::display_t display;
  wayland::registry_t registry = display.get_registry(); 

  wayland::compositor_t compositor;
  wayland::shell_t shell;
  wayland::xdg_wm_base_t xdg_wm_base;
  wayland::seat_t seat;
  wayland::shm_t shm;

  // local objects
  wayland::surface_t surface;
  wayland::shell_surface_t shell_surface;
  wayland::xdg_surface_t xdg_surface;
  wayland::xdg_toplevel_t xdg_toplevel;
  wayland::pointer_t pointer;
  wayland::keyboard_t keyboard;
  wayland::callback_t frame_cb;
  wayland::cursor_image_t cursor_image;
  wayland::buffer_t cursor_buffer;
  wayland::surface_t cursor_surface;

  bool running;

  std::shared_ptr<shared_mem_t> shared_mem;
  //std::array<buffer_t, 2> buffer;
  int cur_buf;

  registry.on_global() = [&] (uint32_t name, const std::string& interface, uint32_t version) {
    spdlog::info("Global interface {} (name {} version {})", interface, name, version);
    
    if(interface == wayland::compositor_t::interface_name)
      registry.bind(name, compositor, version);
    else if(interface == wayland::shell_t::interface_name)
      registry.bind(name, shell, version);
    else if(interface == wayland::xdg_wm_base_t::interface_name)
      registry.bind(name, xdg_wm_base, version);
    else if(interface == wayland::seat_t::interface_name)
      registry.bind(name, seat, version);
    else if(interface == wayland::shm_t::interface_name)
      registry.bind(name, shm, version);
    else if(interface == wayland::output_t::interface_name)
    {
      wayland::output_t output;
      registry.bind(name, output, version);

      // Physical Size of the display
      output.on_geometry() = [=](int32_t x, int32_t y, int32_t physw, int32_t physh, 
        wayland::output_subpixel subp, const std::string& make, const std::string& model, 
        const wayland::output_transform& transform)
      {
        spdlog::info("Output geometry for {}: Maker: {}, Model: {}, X: {}, Y: {}, PW: {} mm, PH: {} mm, SubP: {}, TF: {}", 
          output.get_id(), make, model, x, y, physw, physh, subp, transform);
      };
    
      output.on_scale() = [=](int32_t scale)
      {
        spdlog::info("Output scale for {}: {}", output.get_id(), scale);
      };
  
      output.on_mode() = [=](uint32_t flags, int32_t width, int32_t height, int32_t refresh)
      {
        spdlog::info("Output mode for {}: Width: {}, Height: {}, Refresh: {} hz, Flags: {}",
          output.get_id(), width, height, refresh/1000.0, flags);
      };
    }

  };
  
  // Print global information
  display.roundtrip();
  
  spdlog::info("-----------------------------------");

  seat.on_capabilities() = [&] (const wayland::seat_capability& capability)
  {
    bool has_keyboard = capability & wayland::seat_capability::keyboard;
    bool has_pointer = capability & wayland::seat_capability::pointer;
    spdlog::info("Has Keyboard {}  Has Pointer: {}", has_keyboard, has_pointer);
  };

  seat.on_name() = [&] (const std::string& name) {
    spdlog::info("Name: {}", name);
  };

  surface = compositor.create_surface();

  // create a shell surface
  if(xdg_wm_base)
  {
    xdg_wm_base.on_ping() = [&] (uint32_t serial) { xdg_wm_base.pong(serial); };
    xdg_surface = xdg_wm_base.get_xdg_surface(surface);
    xdg_surface.on_configure() = [&] (uint32_t serial) { xdg_surface.ack_configure(serial); };
    xdg_toplevel = xdg_surface.get_toplevel();
    xdg_toplevel.set_title("Window");
    xdg_toplevel.on_close() = [&] () { running = false; };
    spdlog::info("Creating XDG Window");
  }
  else
  {
    shell_surface = shell.get_shell_surface(surface);
    shell_surface.on_ping() = [&] (uint32_t serial) { shell_surface.pong(serial); };
    shell_surface.set_title("Window");
    shell_surface.set_toplevel();
    spdlog::info("Creating shell Window");
  }
  surface.commit();

  // Print output information
  display.roundtrip();

  // Release outputs
  /*for(auto &output : outputs)
    output.release();
  display.roundtrip();*/

  // event loop
  running = true;
  // while(running)
  //  display.dispatch();
}
