#include "support/settings_host.h"
#include "check.h"
static unsigned calls;
static bool record_setting(const setting_detail_t *setting, uint_fast16_t offset, void *data) { CHECK(setting->id == Setting_ReportInches); CHECK(offset == 0); CHECK(data == &calls); calls++; return true; }
int main(void)
{
    prepare_settings_store();
    const setting_detail_t *setting = setting_get_details(Setting_ReportInches, NULL);
    CHECK(setting != NULL);
    CHECK(settings_iterator(setting, record_setting, &calls));
    CHECK(calls == 1);
    return EXIT_SUCCESS;
}
