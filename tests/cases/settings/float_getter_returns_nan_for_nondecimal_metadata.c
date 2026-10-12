#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); uint32_t stored = 42;
    const setting_detail_t setting = {.id = (setting_id_t)1001, .type = Setting_NonCore,
        .datatype = Format_Integer, .value = &stored};
    CHECK(isnan(setting_get_float_value(&setting, 0))); CHECK(stored == 42);
    return EXIT_SUCCESS;
}
