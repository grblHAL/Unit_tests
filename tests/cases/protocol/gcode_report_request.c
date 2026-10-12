#include "support/engine_host.h"
#include "protocol.h"
#include "override.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(protocol_enqueue_realtime_command(CMD_GCODE_REPORT));
    CHECK(sys.rt_exec_state == EXEC_GCODE_REPORT);
    return EXIT_SUCCESS;
}
