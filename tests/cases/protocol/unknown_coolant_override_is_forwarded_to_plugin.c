#include "support/coolant_host.h"
#include "override.h"
#include "check.h"
static unsigned unknown_calls; static uint8_t unknown_value;
static void record_unknown(uint8_t value) { unknown_calls++; unknown_value = value; }
int main(void)
{
    prepare_coolant(); grbl.on_unknown_accessory_override = record_unknown;
    enqueue_coolant_override(0xEE); CHECK(protocol_exec_rt_system());
    CHECK(unknown_calls == 1); CHECK(unknown_value == 0xEE); CHECK(coolant_calls == 0);
    return EXIT_SUCCESS;
}
