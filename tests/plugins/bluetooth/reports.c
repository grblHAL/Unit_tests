#include "bt_host.h"
int main(void)
{
    bt_prepare(2, true);
    bluetooth_init();
    grbl.on_report_options(true);
    CHECK(bt_prior_reports == 1 && !bt_plugins);
    grbl.on_report_options(false);
    CHECK(bt_prior_reports == 2 && bt_plugins == 1);
    return 0;
}
