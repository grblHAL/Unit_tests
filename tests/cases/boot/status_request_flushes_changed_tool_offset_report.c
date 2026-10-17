#include "support/boot_host.h"
int main(void)
{
    /* Normal reporting includes pending parser changes; the full-status
       command intentionally follows a different report path. Keep a sender
       query/empty line so deferred reports run before this host exits. */
    boot_program = "$10=512\nG43.1Z4\n\x80$G\n\n";
    CHECK(grbl_enter() == 0);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 4);
    CHECK(strstr(engine_output, "<Idle|") != NULL);
    CHECK(strstr(engine_output, "[TLO:0.000,0.000,4.000]") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
