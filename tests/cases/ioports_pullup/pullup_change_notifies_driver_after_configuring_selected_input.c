#include "support/ioports_notifications_host.h"

int main(void)
{
    prepare_io_notifications();
    CHECK(store_io_setting(Settings_IoPort_Pullup_Disable, "2") == Status_OK);
    CHECK(input_config_calls[0] == 0 && input_config_calls[1] == 1);
    CHECK(captured_input[1].pull_mode == PullMode_Down);
    CHECK(io_notification_calls == 1 && io_notified_setting == Settings_IoPort_Pullup_Disable);
    CHECK(store_io_setting(Settings_IoPort_Pullup_Disable, "0") == Status_OK);
    CHECK(input_config_calls[1] == 2 && captured_input[1].pull_mode == PullMode_Up);
    CHECK(io_notification_calls == 2);
    return EXIT_SUCCESS;
}
