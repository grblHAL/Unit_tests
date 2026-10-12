#include "support/settings_validation_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    setting_detail_t detail = {.datatype = Format_XBitfield, .format = "first,second"};
    char valid[] = "3", invalid[] = "4";
    CHECK(setting_validate_me(&detail, 3, valid) == Status_OK);
    CHECK(setting_validate_me(&detail, 4, invalid) == Status_SettingValueOutOfRange);
    return EXIT_SUCCESS;
}
