#pragma once
#include "support/stream_claim_host.h"
static vfs_file_t owned_uart_file;
static io_stream_t file_uart_device;
static unsigned owned_uart_file_closes;
static bool file_uart_release_fails;
static vfs_file_t *open_uart_file(const char *path, const char *mode)
{
    CHECK(strcmp(path, "/job") == 0 && strcmp(mode, "r") == 0);
    return &owned_uart_file;
}
static void close_uart_file(vfs_file_t *file)
{
    CHECK(file == &owned_uart_file && !uart_property.flags.claimed);
    CHECK(receive_disabled && release_calls > 0);
    owned_uart_file_closes++;
}
static const io_stream_t *claim_file_uart(uint32_t baud)
{
    const io_stream_t *device = uart_claim(baud);
    CHECK(device == &uart_device);
    file_uart_device = *device;
    file_uart_device.file = vfs_open("/jobs/job", "r");
    CHECK(file_uart_device.file != NULL);
    return &file_uart_device;
}
static bool release_file_uart(uint8_t instance)
{
    if(file_uart_release_fails) {
        CHECK(instance == 1 && uart_property.flags.claimed);
        release_calls++;
        return false;
    }
    return uart_release(instance);
}
static void prepare_file_uart(void)
{
    prepare_stream_claim();
    static const vfs_t backend = {.fopen = open_uart_file, .fclose = close_uart_file};
    CHECK(vfs_mount(NULL, "/jobs", &backend, (vfs_st_mode_t){.directory = true}));
    uart_property.claim = claim_file_uart;
    uart_property.release = release_file_uart;
    CHECK(stream_open_instance(1, 115200, auxiliary_handler, NULL) == &file_uart_device);
}
