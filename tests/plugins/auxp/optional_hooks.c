#include "auxp_host.h"
int main(void)
{
    auxp_prepare(false);
    hal.port.digital_out(1, true);
    auxp_report(false);
    CHECK(strcmp(output, "|Dout:1") == 0);
    hal.driver_reset();
    auxp_report(false);
    CHECK(strcmp(output, "|Dout:") == 0);
    grbl.on_report_options(false);
    CHECK(strstr(output, "[PLUGIN:AUXP v0.2]") != NULL);
    CHECK(writes == 0 && resets == 0 && reports == 0 && options == 0);
    return 0;
}
