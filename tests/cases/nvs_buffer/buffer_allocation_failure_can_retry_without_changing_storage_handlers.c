#include "support/nvs_allocation_host.h"

int main(void)
{
    prepare_allocation_nvs();
    nvs_io_t original = hal.nvs; fail_buffer_allocations = 1;
    CHECK(!nvs_buffer_alloc());
    CHECK(hal.nvs.type == original.type && hal.nvs.memcpy_to_nvs == original.memcpy_to_nvs);
    CHECK(nvs_buffer_get_physical() == &hal.nvs);
    nvs_buffer_free();
    CHECK(hal.nvs.type == original.type && hal.nvs.memcpy_to_nvs == original.memcpy_to_nvs);
    CHECK(nvs_buffer_get_physical() == &hal.nvs);
    CHECK(nvs_buffer_alloc() && nvs_buffer_init());
    CHECK(hal.nvs.type == NVS_Emulated);
    CHECK(nvs_buffer_get_physical()->memcpy_to_nvs == original.memcpy_to_nvs);
    stored_line_t info = "retained controller information", readback;
    settings_write_build_info(info);
    fail_buffer_allocations = 1;
    CHECK(nvs_buffer_alloc());
    CHECK(fail_buffer_allocations == 1);
    fail_buffer_allocations = 0;
    CHECK(settings_read_build_info(readback));
    CHECK(strcmp(readback, info) == 0);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
