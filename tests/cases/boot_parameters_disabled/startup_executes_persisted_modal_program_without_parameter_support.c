#include "support/boot_host.h"
#if NGC_PARAMETERS_ENABLE || NGC_EXPRESSIONS_ENABLE
#error This case requires the parameters-disabled configuration
#endif
int main(void)
{
    boot_startup_program = "G20G91G18";
    CHECK(grbl_enter() == 0);
    CHECK(boot_setup_calls == 1 && sys.driver_started);
    CHECK(gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);
    CHECK(strstr(engine_output, ">G20G91G18:ok") != NULL);
    return EXIT_SUCCESS;
}
