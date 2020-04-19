#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <spdlog/spdlog.h>
#include <wayland-client.hpp>
#include <wayland-client-protocol-extra.hpp>



int main(int argc, char* argv[]) {

  spdlog::info("Booting up");

  wayland::display_t display;
  wayland::registry_t registry = display.get_registry(); 

  wayland::compositor_t compositor;
  wayland::shell_t shell;
  wayland::xdg_wm_base_t xdg_wm_base;
  wayland::seat_t seat;
  wayland::shm_t shm;

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
        spdlog::info("Output mode for {}: Width: {}, Height: {}, Refresh: {} Mhz, Flags: {}", 
          output.get_id(), width, height, refresh, flags);
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

  // Print output information
  display.roundtrip();

  // Release outputs
  /*for(auto &output : outputs)
    output.release();
  display.roundtrip();*/
}
