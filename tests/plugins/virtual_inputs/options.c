#include "vinput_host.h"
int main(void)
{
    vi_start(true);
    grbl.on_report_options(true);
    CHECK(option_calls == 1);
    grbl.on_report_options(false);
    CHECK(option_calls == 3);
    return 0;
}
