#include "support/debug_serial_host.h"
#include "grbllib.h"
void task_execute_on_startup(void);
int main(void)
{
    prepare_debug_serial();
    sys.cold_start = true;
    debug_reject_claim = true;
    CHECK(!debug_stream_init());
    sys.driver_started = true;
    task_execute_on_startup();
    CHECK(debug_claim_calls == 1);
    CHECK(debug_output[0] == 0);
    CHECK(strstr(engine_output,"Failed to initialize debug stream!") != NULL);
    return 0;
}
