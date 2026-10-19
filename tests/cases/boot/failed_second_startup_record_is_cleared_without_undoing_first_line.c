#include "support/boot_startup_read_host.h"
int main(void)
{
    startup_failed_slot = 1;
    run_startup_record_failure();
    CHECK(gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    CHECK(strcmp(recovered_startup_records[0], "G20") == 0);
    return EXIT_SUCCESS;
}
