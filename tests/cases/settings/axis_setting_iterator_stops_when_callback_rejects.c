#include "support/settings_host.h"
#include "check.h"
static unsigned calls;
static bool stop_axis(const setting_detail_t *setting, uint_fast16_t offset, void *data) { CHECK(setting->id == Setting_AxisMaxRate); CHECK(data == &calls); CHECK(offset == calls); calls++; return offset != 1; }
int main(void)
{
    prepare_settings_store();
    const setting_detail_t *setting = setting_get_details(Setting_AxisMaxRate, NULL);
    CHECK(setting != NULL);
    CHECK(!settings_iterator(setting, stop_axis, &calls));
    CHECK(calls == 2);
    return EXIT_SUCCESS;
}
