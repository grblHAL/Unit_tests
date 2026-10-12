#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    uint8_t byte = 250;
    uint16_t word = 60000;
    uint32_t wide = UINT32_MAX;
    setting_detail_t setting = {.id=(setting_id_t)1001, .type=Setting_NonCore, .datatype=Format_Int8, .value=&byte};
    CHECK(strcmp(setting_get_value(&setting, 0), "250") == 0);
    CHECK(setting_get_int_value(&setting, 0) == 250);
    setting.datatype = Format_Int16;
    setting.value = &word;
    CHECK(strcmp(setting_get_value(&setting, 0), "60000") == 0);
    CHECK(setting_get_int_value(&setting, 0) == 60000);
    setting.datatype = Format_Integer;
    setting.value = &wide;
    CHECK(strcmp(setting_get_value(&setting, 0), "4294967295") == 0);
    CHECK(setting_get_int_value(&setting, 0) == UINT32_MAX);
    return EXIT_SUCCESS;
}
