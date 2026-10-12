#include "support/engine_host.h"
#include "protocol.h"
#include "override.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(!protocol_enqueue_realtime_command('G'));
    CHECK(!protocol_enqueue_realtime_command('1'));
    CHECK(sys.rt_exec_state == 0);
    return EXIT_SUCCESS;
}
