#include "support/system_command_host.h"
#include "support/plugin_numeric_settings_host.h"
int main(void)
{
    prepare_system_command();
    numeric_saved = numeric_live;
    CHECK(settings_register(&numeric_details));
    CHECK(system_command("$1003=42") == Status_OK);
    CHECK(system_command("$100=160") == Status_OK);
    CHECK(numeric_saved.byte == 42 && numeric_saves == 1);
    CHECK(system_command("$RST=&") == Status_OK);
    CHECK(numeric_live.byte == 0 && numeric_saved.byte == 0);
    CHECK(numeric_live.integer == 0 && numeric_saved.integer == 0);
    CHECK(numeric_saves == 2 && numeric_notifications == 2);
    NEAR(settings.axis[X_AXIS].steps_per_mm, 160);
    CHECK(sys.rt_exec_state & EXEC_RESET);
    CHECK(!sys.position_lost);
    return EXIT_SUCCESS;
}
