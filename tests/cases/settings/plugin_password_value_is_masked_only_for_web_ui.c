#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    char password[] = "sample-password";
    const setting_detail_t setting = {.id=(setting_id_t)1001, .type=Setting_NonCore, .datatype=Format_Password, .value=password};
    CHECK(strcmp(setting_get_value(&setting, 0), password) == 0);
    hal.stream.state.webui_connected = true;
    CHECK(strcmp(setting_get_value(&setting, 0), PASSWORD_MASK) == 0);
    CHECK(strcmp(password, "sample-password") == 0);
    hal.stream.state.webui_connected = false;
    CHECK(strcmp(setting_get_value(&setting, 0), password) == 0);
    return EXIT_SUCCESS;
}
