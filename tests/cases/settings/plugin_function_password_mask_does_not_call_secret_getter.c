#include "support/engine_host.h"
#include "check.h"
static unsigned get_calls;
static char *get_plugin_password(setting_id_t id) { CHECK(id == (setting_id_t)1003); get_calls++; return "sample-password"; }
int main(void)
{
    engine_prepare();
    const setting_detail_t setting = {.id=(setting_id_t)1001, .type=Setting_NonCoreFn, .datatype=Format_Password, .get_value=(void *)get_plugin_password};
    hal.stream.state.webui_connected = true;
    CHECK(strcmp(setting_get_value(&setting, 2), PASSWORD_MASK) == 0);
    CHECK(get_calls == 0);
    hal.stream.state.webui_connected = false;
    CHECK(strcmp(setting_get_value(&setting, 2), "sample-password") == 0);
    CHECK(get_calls == 1);
    return EXIT_SUCCESS;
}
