#include "support/settings_validation_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    setting_detail_t detail = {.datatype = Format_Bitfield, .format = "first,second,third"};
    char valid[] = "7", invalid[] = "8";
    CHECK(setting_validate_me(&detail, 7, valid) == Status_OK);
    CHECK(setting_validate_me(&detail, 8, invalid) == Status_SettingValueOutOfRange);
    return EXIT_SUCCESS;
}
