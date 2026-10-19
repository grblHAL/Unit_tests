#include "support/setting_query_host.h"
int main(void)
{
    prepare_setting_query();
    hal.signals_cap = (control_signals_t){.reset = true, .feed_hold = true, .cycle_start = true};
    control_signals_t invert = {.reset = true, .feed_hold = true};
    char value[32];
    snprintf(value, sizeof(value), "%lu", (unsigned long)invert.mask);
    CHECK(store_setting(Setting_ControlInvertMask, value) == Status_OK);
    check_integer_setting_query(Setting_ControlInvertMask, invert.mask);
    invert = (control_signals_t){.cycle_start = true};
    snprintf(value, sizeof(value), "%lu", (unsigned long)invert.mask);
    CHECK(store_setting(Setting_ControlInvertMask, value) == Status_OK);
    check_integer_setting_query(Setting_ControlInvertMask, invert.mask);
    return EXIT_SUCCESS;
}
