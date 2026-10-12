#include "support/settings_validation_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    setting_detail_t detail = {.datatype = Format_Integer, .max_value = "20"};
    char text[] = "21";
    CHECK(setting_validate_me(&detail, 21, text) == Status_SettingValueOutOfRange);
    return EXIT_SUCCESS;
}
