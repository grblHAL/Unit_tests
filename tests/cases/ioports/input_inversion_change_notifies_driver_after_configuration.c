#include "support/ioports_notifications_host.h"

int main(void)
{
    prepare_io_notifications();
    CHECK(store_io_setting(Settings_IoPort_InvertIn, "2") == Status_OK);
    CHECK(input_config_calls[1] == 1 && captured_input[1].inverted);
    CHECK(io_notification_calls == 1 && io_notified_setting == Settings_IoPort_InvertIn);
    CHECK(store_io_setting(Settings_IoPort_InvertIn, "2") == Status_OK);
    CHECK(io_notification_calls == 2 && input_config_calls[1] == 1);
    return EXIT_SUCCESS;
}
