#include "support/nvs_defaults_host.h"
int main(void)
{
    prepare_defaults_storage(NVS_None);
    CHECK(nvs_buffer_init());
    check_restored_storage_defaults();
    CHECK(defaults_failures == 0 && defaults_writes == 0);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
