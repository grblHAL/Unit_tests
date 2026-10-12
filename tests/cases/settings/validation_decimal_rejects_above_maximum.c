#include "support/settings_validation_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    setting_detail_t detail = {.datatype = Format_Decimal, .max_value = "2.5"};
    CHECK(setting_validate_me(&detail, 2.51f, NULL) == Status_SettingValueOutOfRange);
    return EXIT_SUCCESS;
}
