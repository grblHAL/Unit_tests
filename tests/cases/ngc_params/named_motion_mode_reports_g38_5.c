#include "support/probe_motion_host.h"
#include "support/named_parameter_host.h"

int main(void)
{
    prepare_probe_motion();
    away_contact = true;
    contact_steps = 1000;
    CHECK(named_parameter_block("G38.5X1F100") == Status_OK);
    CHECK(sys.alarm == Alarm_None);
    float value = read_named_parameter("_motion_mode");
    fprintf(stderr, "G38.5: _motion_mode=%g, expected 385\n", value);
    NEAR(value, 385);
    return EXIT_SUCCESS;
}
