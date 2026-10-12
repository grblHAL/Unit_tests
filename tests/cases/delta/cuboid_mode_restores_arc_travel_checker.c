#include "support/delta_api_host.h"
#include "report.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    CHECK(grbl.check_arc_travel_limits == NULL);
    CHECK(delta_store(Setting_Kinematics7, "2") == Status_OK);
    CHECK(grbl.check_arc_travel_limits != NULL);
    CHECK(delta_store(Setting_Kinematics7, "0") == Status_OK);
    CHECK(grbl.check_arc_travel_limits == NULL);
    return EXIT_SUCCESS;
}
