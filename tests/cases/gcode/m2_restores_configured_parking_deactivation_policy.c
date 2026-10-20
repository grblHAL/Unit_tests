#include "support/program_end_storage_host.h"
int main(void)
{
    prepare_program_end(false);
    CHECK(store_setting(Setting_ParkingEnable, "7") == Status_OK);
    CHECK(program_block("M56P1") == Status_OK);
    CHECK(!gc_state.modal.override_ctrl.parking_disable);
    CHECK(program_block("M2") == Status_OK);
    CHECK(gc_state.modal.override_ctrl.parking_disable);
    CHECK(sys.override.control.parking_disable);
    return EXIT_SUCCESS;
}
