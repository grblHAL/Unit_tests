#include "fan_host.h"
int main(void)
{
 load_fans(); fan_set_state(0, true); fan_set_state(1, true);
 hal.driver_reset(); CHECK(reset_calls == 1 && !fan_get_state(0) && !fan_get_state(1)); CHECK(!outputs[0] && !outputs[1]);
 fan_set_state(0, true); fan_set_state(1, true);
 grbl.on_program_completed((program_flow_t)0, false);
 CHECK(completed_calls == 1 && !outputs[0] && !outputs[1]);
 CHECK(!fan_get_state(0) && !fan_get_state(1)); return 0;
}
