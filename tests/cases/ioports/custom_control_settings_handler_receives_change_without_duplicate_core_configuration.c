#include "support/ioports_notifications_host.h"
int main(void)
{
    prepare_io_notifications();
    digital_pins[Port_Input][0].function = Input_FeedHold;
    ioport_setting_changed(Setting_ControlInvertMask);
    CHECK(io_notification_calls == 1 && io_notified_setting == Setting_ControlInvertMask);
    CHECK(input_config_calls[0] == 0 && input_config_calls[1] == 0);
    return EXIT_SUCCESS;
}
