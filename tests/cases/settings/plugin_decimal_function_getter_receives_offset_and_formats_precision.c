#include "support/engine_host.h"
#include "check.h"
static unsigned read_calls;
static float read_decimal(setting_id_t id) { CHECK(id == (setting_id_t)1003); read_calls++; return 12.375f; }
int main(void)
{
    engine_prepare();
    setting_detail_t setting = {.id = (setting_id_t)1001, .type = Setting_NonCoreFn,
        .datatype = Format_Decimal, .format = "0.000", .get_value = (void *)read_decimal};
    CHECK(strcmp(setting_get_value(&setting, 2), "12.375") == 0);
    const char *default_formats[] = {NULL, "0"};
    for(unsigned i = 0; i < sizeof(default_formats) / sizeof(default_formats[0]); i++) {
        setting.format = default_formats[i];
        CHECK(strcmp(setting_get_value(&setting, 2), "12.4") == 0);
    }
    NEAR(setting_get_float_value(&setting, 2), 12.375f); CHECK(read_calls == 4);
    return EXIT_SUCCESS;
}
