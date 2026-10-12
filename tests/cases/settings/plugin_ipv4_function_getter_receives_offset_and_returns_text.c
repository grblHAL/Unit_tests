#include "support/engine_host.h"
#include "check.h"
static unsigned read_calls;
static char *read_text(setting_id_t id) { CHECK(id == (setting_id_t)1003); read_calls++; return "192.168.1.40"; }
int main(void)
{
    engine_prepare();
    const setting_detail_t setting = {.id = (setting_id_t)1001, .type = Setting_NonCoreFn,
        .datatype = Format_IPv4, .get_value = (void *)read_text};
    CHECK(strcmp(setting_get_value(&setting, 2), "192.168.1.40") == 0); CHECK(read_calls == 1);
    return EXIT_SUCCESS;
}
