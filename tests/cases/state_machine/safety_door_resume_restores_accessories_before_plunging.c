#include "support/parking_accessory_host.h"
int main(void)
{
    start_powered_parking_move(false);
    park_until_retracted();
    close_and_resume_parking();
    finish_powered_parking();
    CHECK(parking_spindle_state.on && parking_coolant.flood);
    NEAR(parking_spindle_rpm, 5000);
    CHECK(parking_spindle_on_z == -640 && parking_coolant_on_z == -640);
    return EXIT_SUCCESS;
}
