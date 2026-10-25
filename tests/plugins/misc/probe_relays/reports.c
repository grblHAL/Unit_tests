#include "relay_host.h"
int main(void)
{
    load_relays();
    const setting_detail_t *tool = relay_setting(Setting_RelayPortToolsetter);
    const setting_detail_t *second = relay_setting(Setting_RelayPortProbe2);
    CHECK(tool->is_available(tool, 0) && second->is_available(second, 0));
    grbl.on_report_options(true);
    CHECK(options == 1 && reports == 0);
    grbl.on_report_options(false);
    CHECK(options == 2 && reports == 1 && writes == 0 && delays == 0);
    return 0;
}
