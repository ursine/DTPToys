//
// Created by bear on 3/18/20.
//

#pragma once

#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include <memory>

namespace WL {

    // Base class for any objects which come in via the registry
    class RegisteredObject {
    protected:
        uint32_t id;
        const char* const interface;
        void* object;
    public:
        RegisteredObject(uint32_t id, const char *const interface, void* const obj):
                id(id), interface(interface), object(obj)
        {}
        ~RegisteredObject() = default;

        bool operator==(RegisteredObject& other) const
        {
            return this->id == other.id;
        }
    };


    class Display {
    private:
        // Raw data type pointers
        wl_display* display = nullptr;
        wl_registry* registry = nullptr;

    public:
        Display();
        ~Display();

        int dispatch() { return wl_display_dispatch(display); }
        int roundtrip() { return wl_display_roundtrip(display); }
        int get_fd() { return wl_display_get_fd(display); }
        int flush() { return wl_display_flush(display); }

        wl_display* get_ptr() { return display; }
    };

}
