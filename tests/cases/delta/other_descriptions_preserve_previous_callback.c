#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    CHECK(strcmp(grbl.on_setting_get_description(Setting_AxisMaxRate), "fixture description") == 0);
    CHECK(delta_description_calls == 1);
    return EXIT_SUCCESS;
}
