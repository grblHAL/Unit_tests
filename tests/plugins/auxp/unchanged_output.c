#include "auxp_host.h"
int main(void)
{
    auxp_prepare(true);
    hal.port.digital_out(2, true);
    auxp_report(false);
    hal.port.digital_out(2, true);
    hal.port.digital_out(6, false);
    auxp_report(false);
    CHECK(strcmp(output, "|previous") == 0);
    CHECK(writes == 3);
    auxp_report(true);
    CHECK(strcmp(output, "|Dout:2|previous") == 0);
    return 0;
}
