#include "stm_host.h"
int main(void)
{
    const unsigned sizes[] = {4, 32, 128};
    for (unsigned n = 0; n < 3; n++)
    {
        stm_prepare(sizes[n]);
        CHECK(memcpy_to_flash((uint8_t *)stm_source));
        stm_check_copy();
        for (unsigned i = sizes[n]; i < 128; i++)
            CHECK(((uint8_t *)stm_flash_words)[i] == 0xff);
    }
    return 0;
}
