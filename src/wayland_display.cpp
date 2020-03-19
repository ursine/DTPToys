//
// Created by bear on 3/18/20.
//

#include "wayland_display.h"

WL::Display::Display() {
    display.reset(wl_display_connect(nullptr), wl_display_disconnect);

    if (display == nullptr) {
        fprintf(stderr, "Can't connect to display\n");
        exit(1);
    }
    printf("connected to display\n");
}

WL::Display::~Display() {
    printf("disconnected from display\n");
}

