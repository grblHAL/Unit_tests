#include "support/protocol_host.h"
#include "state_machine.h"
#include <string.h>
#include "check.h"

int main(void)
{
    prepare_protocol();
    state_set(STATE_IDLE);
    gc_state.file_run = true;
    gc_state.modal.program_flow = ProgramFlow_Running;
    char jog[] = "$J=G91X1F100", command[] = "G20";
    CHECK(!protocol_enqueue_gcode(jog));
    CHECK(protocol_enqueue_gcode(command));
    return EXIT_SUCCESS;
}
