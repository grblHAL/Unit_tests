#include "key_host.h"
int main(void)
{
    key_prepare();
    key_load();
    CHECK(key_modes == 1 && key_data_changes == 1);
    key_press('h');
    CHECK(key_data.mode == JogMode_Slow);
    key_press('h');
    CHECK(key_data.mode == JogMode_Step);
    key_press('h');
    CHECK(key_data.mode == JogMode_Fast);
    for (unsigned i = 0; i < 3; i++)
        key_press('m');
    CHECK(key_data.modifier_index == 0 && key_modes == 4);
    grbl.on_report_options(true);
    grbl.on_report_options(false);
    CHECK(key_previous_reports == 2 && !strstr(key_version, "not connected"));
    return 0;
}
