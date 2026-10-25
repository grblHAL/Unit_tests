#include "auxp_host.h"
int main(void)
{
    auxp_prepare(true);
    auxp_report(false);
    hal.port.digital_out(8, true);
    hal.port.digital_out(255, true);
    auxp_report(false);
    CHECK(strcmp(output, "|previous") == 0);
    CHECK(writes == 2 && last_port == 255 && last_value);
    auxp_report(true);
    CHECK(strcmp(output, "|Dout:|previous") == 0);
    return 0;
}
