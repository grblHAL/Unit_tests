#include "support/system_metadata_host.h"
int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$B - toggle block delete switch") != NULL);
    CHECK(strstr(metadata_output, "$O - toggle optional stop switch") != NULL);
    CHECK(strstr(metadata_output, "$S - toggle single stepping switch") != NULL);
    metadata_output[0] = 0;
    hal.signals_cap.block_delete = true;
    hal.signals_cap.stop_disable = true;
    hal.signals_cap.single_block = true;
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$B - toggle block delete switch") == NULL);
    CHECK(strstr(metadata_output, "$O - toggle optional stop switch") == NULL);
    CHECK(strstr(metadata_output, "$S - toggle single stepping switch") == NULL);
    CHECK(strstr(metadata_output, "$G - output parser state") != NULL);
    return EXIT_SUCCESS;
}
