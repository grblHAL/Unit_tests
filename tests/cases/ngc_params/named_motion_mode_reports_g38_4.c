#include "support/probe_motion_host.h"
#include "support/named_parameter_host.h"

int main(void)
{
    prepare_probe_motion();
    away_contact = true;
    CHECK(named_parameter_block("G38.4X1F100") == Status_OK);
    CHECK(sys.alarm == Alarm_None);
    float value = read_named_parameter("_motion_mode");
    fprintf(stderr, "G38.4: _motion_mode=%g, expected 384\n", value);
    NEAR(value, 384);
    return EXIT_SUCCESS;
}
