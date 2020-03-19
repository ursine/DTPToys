//
// Created by bear on 3/18/20.
//

#include "wayland_registry.h"

#include <utility>

WL::Registry::Registry(std::shared_ptr<wl_display> d):display(std::move(d)) {
    registry.reset(wl_display_get_registry(display.get()));
}

