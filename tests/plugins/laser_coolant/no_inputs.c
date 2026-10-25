#include "coolant_host.h"
int main(void)
{
    coolant_prepare(false);
    CHECK(!coolant_settings && coolant_warnings == 1);
    hal.coolant.set_state((coolant_state_t){.flood = On});
    CHECK(coolant_output.flood && !coolant_irqs);
    return 0;
}
