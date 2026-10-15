#include "support/ioports_notifications_host.h"

int main(void)
{
    prepare_io_notifications();
    digital_pins[Port_Output][0].mode.open_drain = true;
    CHECK(store_io_setting(Settings_IoPort_InvertOut, "1") == Status_OK);
    CHECK(output_config_calls[0] == 1);
    CHECK(captured_output[0].inverted && captured_output[0].open_drain);
    CHECK(io_notification_calls == 1 && io_notified_setting == Settings_IoPort_InvertOut);
    return EXIT_SUCCESS;
}
