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
    CHECK(css_block("S1500") == Status_OK);
    NEAR(read_named_parameter("_rpm"), 1500);
    CHECK(css_block("S2500") == Status_OK);
    NEAR(read_named_parameter("_rpm"), 2500);
    return EXIT_SUCCESS;
}
