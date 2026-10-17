#include "support/protocol_file_host.h"
int main(void)
{
    run_protocol_file("G999\nG20\n");
    CHECK(protocol_file_errors >= 1);
    CHECK(protocol_file_error_status == Status_GcodeUnsupportedCommand);
    CHECK(protocol_file_end_status == Status_GcodeUnsupportedCommand);
    CHECK(!gc_state.modal.units_imperial);
    CHECK(gc_state.last_error == Status_OK); /* The restored sender's $G query succeeds. */
    return EXIT_SUCCESS;
}
