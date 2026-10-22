#include "support/cutter_capture_host.h"
#include "report.h"
static bool sender_connected(void) { return true; }
int main(void)
{
    prepare_cutter_capture();
    report_init_fns();
    hal.stream.is_connected = sender_connected;
    CHECK(cutter_block("G41.1D6") == Status_OK);
    CHECK(cutter_block("M2") == Status_OK);
    CHECK(cutter_enable_calls == 2);
    CHECK(cutter_received.side == CComp_Off);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Off);
    CHECK(!HOST_PARSER_FLAGS.ccomp_off);
    CHECK(plan_get_current_block() == NULL);
    CHECK(strstr(engine_output, "[MSG:Pgm End]") != NULL);
    return EXIT_SUCCESS;
}
