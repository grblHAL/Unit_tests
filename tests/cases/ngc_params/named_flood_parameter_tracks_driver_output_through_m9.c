#include "support/coolant_host.h"
#include "support/named_parameter_host.h"
int main(void)
{
    prepare_coolant();
    hal.coolant_cap.mist = hal.coolant_cap.flood = true;
    CHECK(named_parameter_block("M8") == Status_OK);
    CHECK(actual_coolant.flood && !actual_coolant.mist);
    NEAR(read_named_parameter("_flood"), 1);
    NEAR(read_named_parameter("_mist"), 0);
    CHECK(named_parameter_block("M9") == Status_OK);
    CHECK(!actual_coolant.mist && !actual_coolant.flood);
    NEAR(read_named_parameter("_mist"), 0);
    NEAR(read_named_parameter("_flood"), 0);
    CHECK(coolant_calls == 2);
    return EXIT_SUCCESS;
}
