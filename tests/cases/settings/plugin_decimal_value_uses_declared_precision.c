#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    float stored = 12.375f;
    const setting_detail_t setting = {.id=(setting_id_t)1001, .type=Setting_NonCore, .datatype=Format_Decimal, .format="0.000", .value=&stored};
    CHECK(strcmp(setting_get_value(&setting, 0), "12.375") == 0);
    NEAR(setting_get_float_value(&setting, 0), 12.375f);
    return EXIT_SUCCESS;
}
