#include "support/system_metadata_host.h"
#include "support/plugin_numeric_settings_host.h"
int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$RST=&") == NULL);
    numeric_saved = numeric_live;
    CHECK(settings_register(&numeric_details));
    metadata_output[0] = 0;
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$RST=& - restore driver and plugin default settings.") != NULL);
    CHECK(numeric_saves == 0 && numeric_notifications == 0);
    return EXIT_SUCCESS;
}
