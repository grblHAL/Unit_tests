#include "support/settings_validation_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    setting_detail_t detail = {.datatype = Format_Decimal};
    CHECK(setting_validate_me(&detail, -0.5f, NULL) == Status_NegativeValue);
    return EXIT_SUCCESS;
}
