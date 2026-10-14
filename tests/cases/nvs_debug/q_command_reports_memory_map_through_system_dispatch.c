#include "support/nvs_debug_host.h"
#include "system.h"
int main(void)
{
    prepare_nvs_debug(); char command[] = "$Q";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    check_core_memory_map();
    return EXIT_SUCCESS;
}
