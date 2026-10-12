#include "support/protocol_host.h"
#include "state_machine.h"
#include <string.h>
#include "check.h"

int main(void)
{
    prepare_protocol();
    state_set(STATE_IDLE);
    char block[LINE_BUFFER_SIZE + 1];
    memset(block, 'X', LINE_BUFFER_SIZE);
    block[LINE_BUFFER_SIZE] = '\0';
    CHECK(!protocol_enqueue_gcode(block));
    char valid[] = "G20";
    CHECK(protocol_enqueue_gcode(valid));
    return EXIT_SUCCESS;
}
