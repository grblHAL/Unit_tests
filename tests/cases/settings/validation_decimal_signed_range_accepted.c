#include "support/settings_validation_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    setting_detail_t detail = {.datatype = Format_Decimal, .min_value = "-2", .max_value = "-1"};
    CHECK(setting_validate_me(&detail, -1.5f, NULL) == Status_OK);
    return EXIT_SUCCESS;
}
