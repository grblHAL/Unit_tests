#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    char command[] = "$DELTA";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(strstr(engine_output, "Delta robot:" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "Rectangular cuboid envelope:") != NULL);
    CHECK(strstr(engine_output, "Resolution:") != NULL);
    CHECK(strstr(engine_output, "0.00,0.00,0.00 deg") != NULL);
    return EXIT_SUCCESS;
}
