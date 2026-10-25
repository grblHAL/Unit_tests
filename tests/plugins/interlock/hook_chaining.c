#include "interlock_host.h"
int main(void)
{
    il_start();
    unsigned previous = chains;
    CHECK(grbl.on_spindle_select(&spindle));
    CHECK(grbl.on_spindle_select(&spindle));
    il_command(true);
    CHECK(hardware_spindles == 1 && chains == previous + 2);
    select_ok = false;
    CHECK(!grbl.on_spindle_select(&spindle));
    grbl.on_report_options(true);
    grbl.on_report_options(false);
    CHECK(chains == previous + 6);
    return 0;
}
