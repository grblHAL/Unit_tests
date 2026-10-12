#include "support/named_parameter_host.h"
#include "support/css_host.h"
#include "protocol.h"
#include "check.h"
static control_signals_t spindle_parameter_controls(void) { return (control_signals_t){0}; }

int main(void)
{
    prepare_css_parser(true);
    grbl.on_execute_realtime = protocol_execute_noop;
    hal.control.get_state = spindle_parameter_controls;
    CHECK(css_block("M3S1000") == Status_OK);
    NEAR(read_named_parameter("_spindle_on"), 1);
    fprintf(stderr, "M3: ccw=%u _spindle_cw=%g expected=1\n", gc_spindle_get(0)->state.ccw, read_named_parameter("_spindle_cw"));
    NEAR(read_named_parameter("_spindle_cw"), 1);
    return EXIT_SUCCESS;
}
