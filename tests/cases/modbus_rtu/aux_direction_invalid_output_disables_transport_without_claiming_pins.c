#include "support/rtu_aux_direction_host.h"

int main(void)
{
    CHECK(!initialize_rtu_transport(NULL, 2, configure_rtu_aux_outputs));
    CHECK(!hal.driver_cap.modbus_rtu);
    CHECK(sys.alarm == Alarm_SelftestFailed);
    CHECK(!modbus_isup().rtu);
    CHECK(direction_assignments == 0 && output_calls == 0);
    CHECK(!digital_pins[Port_Output][0].mode.claimed);
    CHECK(!digital_pins[Port_Output][1].mode.claimed);
    return EXIT_SUCCESS;
}
