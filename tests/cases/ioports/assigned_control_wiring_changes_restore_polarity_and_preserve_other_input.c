#include "support/ioports_settings_host.h"

static control_signals_t read_controls(void) { return (control_signals_t){0}; }
static bool assign_control(xbar_t *pin, pin_function_t function)
{
    CHECK(pin == &digital_pins[Port_Input][0]);
    CHECK(function == Input_FeedHold);
    return true;
}
int main(void)
{
    prepare_io_settings();
    hal.control.get_state = read_controls;
    xbar_t *hold = hal.port.get_pin_info(Port_Digital, Port_Input, 0);
    hold->set_function = assign_control;
    hold->mode.debounce = true;
    control_signals_t capability = {.feed_hold = true};
    CHECK(ioport_set_function(hold, Input_FeedHold, (driver_caps_t){.control = &capability}));
    unsigned other_calls = input_config_calls[1];
    char mask[16];
    snprintf(mask, sizeof(mask), "%u", (unsigned)capability.mask);
    CHECK(store_io_setting(Setting_ControlInvertMask, mask) == Status_OK);
    CHECK(captured_input[0].inverted && captured_input[0].debounce);
    CHECK(captured_input[0].pull_mode == PullMode_Up);
    CHECK(settings.ioport.invert_in.mask & 1);
    CHECK(store_io_setting(Setting_ControlPullUpDisableMask, mask) == Status_OK);
    CHECK(captured_input[0].inverted && captured_input[0].debounce);
    CHECK(captured_input[0].pull_mode == PullMode_Down);
    CHECK(store_io_setting(Setting_ControlInvertMask, "0") == Status_OK);
    CHECK(!captured_input[0].inverted && captured_input[0].debounce);
    CHECK(!(settings.ioport.invert_in.mask & 1));
    CHECK(store_io_setting(Setting_ControlPullUpDisableMask, "0") == Status_OK);
    CHECK(captured_input[0].pull_mode == PullMode_Up);
    CHECK(!captured_input[0].inverted && captured_input[0].debounce);
    CHECK(input_config_calls[1] == other_calls);
    CHECK(hold->function == Input_FeedHold && hal.signals_cap.feed_hold);
    return EXIT_SUCCESS;
}
