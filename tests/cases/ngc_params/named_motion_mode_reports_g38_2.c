#include "support/probe_motion_host.h"
#include "support/named_parameter_host.h"

int main(void)
{
    prepare_probe_motion();
    CHECK(named_parameter_block("G38.2X1F100") == Status_OK);
    CHECK(sys.alarm == Alarm_None);
    float value = read_named_parameter("_motion_mode");
    fprintf(stderr, "G38.2: _motion_mode=%g, expected 382\n", value);
    NEAR(value, 382);
    return EXIT_SUCCESS;
}
