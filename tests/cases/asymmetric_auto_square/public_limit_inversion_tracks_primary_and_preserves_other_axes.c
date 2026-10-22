#include "support/square_host.h"

int main(void)
{
    prepare_square();
    unsigned before = settings_callbacks;
    char invert_y[] = "2";
    CHECK(settings_store_setting(Setting_LimitPinsInvertMask, invert_y) == Status_OK);
    CHECK(settings.limits.invert.mask == (Y_AXIS_BIT | (1u << 3)));
    CHECK(settings_callbacks == before + 1);
    char invert_x[] = "1";
    CHECK(settings_store_setting(Setting_LimitPinsInvertMask, invert_x) == Status_OK);
    CHECK(settings.limits.invert.mask == X_AXIS_BIT);
    CHECK(settings_callbacks == before + 2);
    char clear[] = "0";
    CHECK(settings_store_setting(Setting_LimitPinsInvertMask, clear) == Status_OK);
    CHECK(settings.limits.invert.mask == 0 && settings_callbacks == before + 3);
    return EXIT_SUCCESS;
}
