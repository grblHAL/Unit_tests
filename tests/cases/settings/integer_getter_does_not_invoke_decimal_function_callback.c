#include "support/engine_host.h"
#include "check.h"
static unsigned read_calls;
static float read_decimal(setting_id_t id) { (void)id; read_calls++; return 12.375f; }
int main(void)
{
    engine_prepare();
    const setting_detail_t setting = {.id = (setting_id_t)1001, .type = Setting_NonCoreFn,
        .datatype = Format_Decimal, .get_value = (void *)read_decimal};
    CHECK(setting_get_int_value(&setting, 0) == 0); CHECK(read_calls == 0);
    return EXIT_SUCCESS;
}
