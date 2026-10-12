#include "support/protocol_host.h"
#include "state_machine.h"
#include <string.h>
#include "check.h"

int main(void)
{
    prepare_protocol();
    state_set(STATE_IDLE);
    sys.rt_exec_state = EXEC_MOTION_CANCEL;
    char block[] = "G20";
    CHECK(!protocol_enqueue_gcode(block));
    sys.rt_exec_state = EXEC_MOTION_CANCEL_FAST;
    CHECK(!protocol_enqueue_gcode(block));
    sys.rt_exec_state = 0;
    CHECK(protocol_enqueue_gcode(block));
    return EXIT_SUCCESS;
}
