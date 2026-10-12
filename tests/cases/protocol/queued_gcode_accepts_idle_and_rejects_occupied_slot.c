#include "support/protocol_host.h"
#include "state_machine.h"
#include <string.h>
#include "check.h"

int main(void)
{
    prepare_protocol();
    state_set(STATE_IDLE);
    char first[] = "G20", second[] = "G21";
    CHECK(protocol_enqueue_gcode(first));
    CHECK(!protocol_enqueue_gcode(second));
    return EXIT_SUCCESS;
}
