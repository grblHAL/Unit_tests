#include "support/engine_host.h"
#include "probe.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(!probe_add(Probe_Default, 0, IRQ_Mode_None, NULL, NULL));
    CHECK(hal.probe.get_state == NULL);
    return EXIT_SUCCESS;
}
