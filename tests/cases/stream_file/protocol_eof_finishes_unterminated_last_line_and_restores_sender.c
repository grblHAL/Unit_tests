#include "support/protocol_file_host.h"
int main(void)
{
    run_protocol_file("G20\nG91");
    CHECK(protocol_file_end_status == Status_OK && protocol_file_errors == 0);
    CHECK(gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    CHECK(strstr(engine_output, "G20 G91") != NULL);
    return EXIT_SUCCESS;
}
