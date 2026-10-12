#include "support/engine_host.h"
#include "check.h"
static unsigned get_calls;
static uint32_t get_plugin_value(setting_id_t id) { CHECK(id == (setting_id_t)1003); get_calls++; return 60000; }
int main(void)
{
    engine_prepare();
    const setting_detail_t setting = {.id=(setting_id_t)1001, .type=Setting_NonCoreFn, .datatype=Format_Integer, .get_value=(void *)get_plugin_value};
    CHECK(strcmp(setting_get_value(&setting, 2), "60000") == 0);
    CHECK(setting_get_int_value(&setting, 2) == 60000);
    CHECK(get_calls == 2);
    return EXIT_SUCCESS;
}
