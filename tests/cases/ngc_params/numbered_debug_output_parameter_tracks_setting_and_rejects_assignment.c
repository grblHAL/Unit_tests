#include "support/settings_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_settings_store();
    float value;
    CHECK(store_setting(Setting_NGCDebugOut, "0") == Status_OK);
    CHECK(ngc_param_get(5599, &value)); NEAR(value, 0);
    CHECK(store_setting(Setting_NGCDebugOut, "1") == Status_OK);
    CHECK(ngc_param_get(5599, &value)); NEAR(value, 1);
    CHECK(!ngc_param_set(5599, 0));
    CHECK(settings.flags.ngc_debug_out);
    CHECK(store_setting(Setting_NGCDebugOut, "0") == Status_OK);
    CHECK(ngc_param_get(5599, &value)); NEAR(value, 0);
    return EXIT_SUCCESS;
}
