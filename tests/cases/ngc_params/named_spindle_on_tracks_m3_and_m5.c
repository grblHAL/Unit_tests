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
    CHECK(css_block("M3S1000") == Status_OK);
    NEAR(read_named_parameter("_spindle_on"), 1);
    CHECK(css_block("M5") == Status_OK);
    NEAR(read_named_parameter("_spindle_on"), 0);
    return EXIT_SUCCESS;
}
