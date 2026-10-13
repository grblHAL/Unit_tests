#include "support/probe_motion_host.h"
#include "support/named_parameter_host.h"

int main(void)
{
    prepare_probe_motion();
    contact_steps = 1000;
    CHECK(named_parameter_block("G38.3X1F100") == Status_OK);
    CHECK(sys.alarm == Alarm_None);
    float value = read_named_parameter("_motion_mode");
    fprintf(stderr, "G38.3: _motion_mode=%g, expected 383\n", value);
    NEAR(value, 383);
    return EXIT_SUCCESS;
}
