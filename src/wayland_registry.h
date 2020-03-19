//
// Created by bear on 3/18/20.
//

#pragma once

#include <memory>
#include <wayland-client.h>


namespace WL {

    class Registry {
    private:
        std::shared_ptr<wl_display> display = nullptr;
        std::shared_ptr<wl_registry> registry = nullptr;

    public:
        Registry(std::shared_ptr<wl_display> d);
        ~Registry();
    };

}