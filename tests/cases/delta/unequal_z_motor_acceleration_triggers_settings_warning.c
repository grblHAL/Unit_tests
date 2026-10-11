#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    settings.axis[Z_AXIS].acceleration = 101;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    char command[] = "$DELTA";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(strstr(engine_output, "WARNING: Review settings!") != NULL);
    return EXIT_SUCCESS;
}
