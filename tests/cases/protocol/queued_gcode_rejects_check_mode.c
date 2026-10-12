#include "support/protocol_host.h"
#include "state_machine.h"
#include <string.h>
#include "check.h"

int main(void)
{
    prepare_protocol();
    CHECK(state_get() == STATE_CHECK_MODE);
    char block[] = "G20";
    CHECK(!protocol_enqueue_gcode(block));
    return EXIT_SUCCESS;
}
