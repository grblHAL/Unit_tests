#include "support/nvs_allocation_host.h"
#include <string.h>
void task_execute_on_startup(void);

int main(void)
{
    prepare_allocation_nvs(); fail_buffer_allocations = 1;
    sys.cold_start = true;
    CHECK(!nvs_buffer_alloc()); CHECK(!nvs_buffer_init());
    CHECK(hal.nvs.type == NVS_EEPROM);
    CHECK(engine_output[0] == 0);
    sys.driver_started = true;
    task_execute_on_startup();
    CHECK(strstr(engine_output, "Not enough heap for NVS buffer!") != NULL);
    return EXIT_SUCCESS;
}
