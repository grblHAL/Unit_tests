#include "support/rtu_host.h"

int main(void)
{
    CHECK(!initialize_rtu_transport(NULL, -1, NULL));
    CHECK(!hal.driver_cap.modbus_rtu);
    CHECK(sys.alarm == Alarm_SelftestFailed);
    CHECK(!modbus_isup().rtu);
    return EXIT_SUCCESS;
}
