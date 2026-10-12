#include "support/settings_host.h"
#include "check.h"
static unsigned calls, seen_offsets;
static bool axis_available(const setting_detail_t *setting, uint_fast16_t offset) { CHECK(setting->id == (setting_id_t)1001); return offset != Y_AXIS; }
static bool record_available(const setting_detail_t *setting, uint_fast16_t offset, void *data) { CHECK(setting->id == (setting_id_t)1001); CHECK(data == &calls); CHECK(offset != Y_AXIS); seen_offsets |= 1u << offset; calls++; return true; }
int main(void)
{
    prepare_settings_store();
    uint32_t value = 0;
    const setting_detail_t setting = {.id=(setting_id_t)1001, .group=Group_Axis0, .type=Setting_NonCore, .datatype=Format_Integer, .value=&value, .is_available=axis_available};
    CHECK(settings_iterator(&setting, record_available, &calls));
    CHECK(calls == 2);
    CHECK(seen_offsets == (X_AXIS_BIT | Z_AXIS_BIT));
    return EXIT_SUCCESS;
}
