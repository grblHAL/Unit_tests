#include "auxp_host.h"
int main(void)
{
    auxp_prepare(true);
    auxp_report(false);
    hal.port.digital_out(7, true);
    hal.port.digital_out(0, true);
    hal.port.digital_out(3, true);
    auxp_report(false);
    CHECK(strcmp(output, "|Dout:037|previous") == 0);
    CHECK(writes == 3 && last_port == 3 && last_value);
    hal.port.digital_out(3, false);
    auxp_report(false);
    CHECK(strcmp(output, "|Dout:07|previous") == 0);
    CHECK(writes == 4 && !last_value);
    return 0;
}
