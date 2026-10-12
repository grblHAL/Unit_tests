#include "support/engine_host.h"
#include "protocol.h"
#include "override.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_COOLANT_FLOOD_TOGGLE));
    CHECK(get_coolant_override() == CMD_OVERRIDE_COOLANT_FLOOD_TOGGLE);
    CHECK(get_coolant_override() == 0);
    return EXIT_SUCCESS;
}
