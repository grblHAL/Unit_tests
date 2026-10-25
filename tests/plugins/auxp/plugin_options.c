#include "auxp_host.h"
int main(void)
{
    auxp_prepare(true);
    grbl.on_report_options(true);
    CHECK(options == 1 && output[0] == 0);
    grbl.on_report_options(false);
    CHECK(options == 2);
    CHECK(strcmp(output, "[PLUGIN:AUXP v0.2]" ASCII_EOL) == 0);
    return 0;
}
