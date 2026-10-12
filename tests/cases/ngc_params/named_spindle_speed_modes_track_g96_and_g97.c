#include "support/named_parameter_host.h"
#include "support/css_host.h"
#include "protocol.h"
#include "check.h"
static control_signals_t controls(void) { return (control_signals_t){0}; }
int main(void)
{
    prepare_css_parser(true);
    grbl.on_execute_realtime = protocol_execute_noop;
    hal.control.get_state = controls;
    CHECK(css_block("G96S100") == Status_OK);
    NEAR(read_named_parameter("_spindle_css_mode"), 1);
    NEAR(read_named_parameter("_spindle_rpm_mode"), 0);
    CHECK(css_block("G97S1500") == Status_OK);
    NEAR(read_named_parameter("_spindle_css_mode"), 0);
    NEAR(read_named_parameter("_spindle_rpm_mode"), 1);
    return EXIT_SUCCESS;
}
