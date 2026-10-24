#include "auxp_host.h"
int main(void)
{
    auxp_prepare(true);
    for (uint8_t i = 0; i < 8; i++)
        hal.port.digital_out(i, true);
    auxp_report(false);
    CHECK(strcmp(output, "|Dout:01234567|previous") == 0);
    hal.driver_reset();
    CHECK(resets == 1 && writes == 8);
    auxp_report(false);
    CHECK(strcmp(output, "|Dout:|previous") == 0);
    auxp_report(false);
    CHECK(strcmp(output, "|previous") == 0);
    return 0;
}
