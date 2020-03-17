#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <wayland-client.h>
#include <memory>

static struct wl_compositor *compositor = nullptr;
static struct wl_surface *surface;
static struct wl_shell *shell;
static struct wl_shell_surface *shell_surface;

static void global_registry_handler(void *data,
                                    struct wl_registry *registry,
                                    uint32_t id,
                                    const char *interface,
                                    uint32_t version) {
    printf("Got a registry event for %s id %d\n", interface, id);
    if (strcmp(interface, "wl_compositor") == 0) {
        compositor = (struct wl_compositor *) wl_registry_bind(registry,
                                                               id,
                                                               &wl_compositor_interface,
                                                               1);
    } else if (strcmp(interface, "wl_shell") == 0) {
        shell = (struct wl_shell *) wl_registry_bind(registry, id,
                                                     &wl_shell_interface, 1);
    }
}

static void global_registry_remover(void *data,
                                    struct wl_registry *registry,
                                    uint32_t id) {
    printf("Got a registry losing event for %d\n", id);
}

static const struct wl_registry_listener registry_listener = {
        global_registry_handler,
        global_registry_remover
};


namespace WL {
class Display {
private:
    std::shared_ptr<wl_display> display = nullptr;

public:
    Display() {
        display.reset(wl_display_connect(nullptr),
                wl_display_disconnect);

        if (display == nullptr) {
            fprintf(stderr, "Can't connect to display\n");
            exit(1);
        }
        printf("connected to display\n");
    }

    ~Display() {
        printf("disconnected from display\n");
    }

    int dispatch() { return wl_display_dispatch(display.get()); }

    int roundtrip() { return wl_display_roundtrip(display.get()); }

    wl_registry* get_registry() {
        return wl_display_get_registry(display.get());
    }

    std::shared_ptr<wl_display> get_ptr() { return display; }
};

}

int main(int argc, char *argv[]) {

    std::unique_ptr<WL::Display> display = std::make_unique<WL::Display>();

    wl_registry *registry = display->get_registry();
    wl_registry_add_listener(registry, &registry_listener, nullptr);

    display->dispatch();
    display->roundtrip();

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


