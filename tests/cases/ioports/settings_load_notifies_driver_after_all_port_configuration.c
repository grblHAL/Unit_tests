#include "support/ioports_notifications_host.h"

int main(void)
{
    prepare_io_notifications();
    sys.ioinit_pending = true;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(io_loaded_calls == 1);
    CHECK(io_notification_calls == 0);
    return EXIT_SUCCESS;
}
