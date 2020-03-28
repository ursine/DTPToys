#include <cstdio>
#include <wayland-client.h>
#include <memory>

#include "wayland_display.h"
#include "gc_logging_utils.h"

static struct wl_compositor *compositor = nullptr;
static struct wl_surface *surface;
static struct wl_shell *shell;
static struct wl_shell_surface *shell_surface;


int main(int argc, char *argv[]) {

    const auto logger = GC::log_get("main");

    logger->info("Getting Wayland Connection");

    std::unique_ptr<WL::Display> display = std::make_unique<WL::Display>();

    if (compositor == nullptr) {
        fprintf(stderr, "Can't find compositor\n");
        exit(1);
    } else {
        fprintf(stderr, "Found compositor\n");
    }

    surface = wl_compositor_create_surface(compositor);
    if (surface == nullptr) {
        fprintf(stderr, "Can't create surface\n");
        exit(1);
    } else {
        fprintf(stderr, "Created surface\n");
    }

    shell_surface = wl_shell_get_shell_surface(shell, surface);
    if (shell_surface == nullptr) {
        fprintf(stderr, "Can't create shell surface\n");
        exit(1);
    } else {
        fprintf(stderr, "Created shell surface\n");
    }
    wl_shell_surface_set_toplevel(shell_surface);

    return 0;
}


