//
// Created by bear on 3/18/20.
//

#pragma once

#include <wayland-client.h>
#include <memory>

namespace WL {

    class Display {
    private:
        std::shared_ptr<wl_display> display = nullptr;

    public:
        Display();
        ~Display();

        int dispatch() { return wl_display_dispatch(display.get()); }

        int roundtrip() { return wl_display_roundtrip(display.get()); }

        std::shared_ptr<wl_display> get_ptr() { return display; }
    };

}
