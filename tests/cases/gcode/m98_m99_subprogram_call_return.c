#include "support/incoming_macro_host.h"
static unsigned returned;
static void macro_returned(void) { returned++; }
int main(void)
{
    prepare_incoming_macro();
    hal.control.get_state = incoming_controls;
    hal.stream.is_connected = incoming_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    grbl.on_macro_return = macro_returned;
    state_set(STATE_IDLE);
    CHECK(incoming_block("M98P100") == Status_OK);
    CHECK(macro_calls == 1 && incoming_called_macro == 100);
    CHECK(incoming_block("M99") == Status_OK);
    CHECK(returned == 1);
    return EXIT_SUCCESS;
}
