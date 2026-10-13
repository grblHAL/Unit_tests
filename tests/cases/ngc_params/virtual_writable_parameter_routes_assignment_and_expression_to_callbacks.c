#include "support/virtual_param_host.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(ngc_virtual_rw_param_add("_sensor", read_virtual_sensor, write_virtual_sensor));
    char assignment[] = "#<_sensor>=21";
    CHECK(gc_execute_block(assignment) == Status_OK);
    CHECK(virtual_writes == 1);
    NEAR(virtual_sensor_value, 21);
    char move[] = "G1X[#<_sensor>+1]F100";
    CHECK(gc_execute_block(move) == Status_OK);
    NEAR(gc_state.position[X_AXIS], 22);
    CHECK(virtual_writes == 1);
    return EXIT_SUCCESS;
}
