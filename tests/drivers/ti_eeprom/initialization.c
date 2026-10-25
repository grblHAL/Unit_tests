#include "ti_host.h"
int main(void)
{
    ti_prepare();
    CHECK(hal.nvs.get_byte && hal.nvs.put_byte && hal.nvs.memcpy_to_nvs && hal.nvs.memcpy_from_nvs);
    CHECK(reads == 0 && writes == 0);
    return 0;
}
