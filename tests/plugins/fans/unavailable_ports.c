#include "fan_host.h"
int main(void)
{
 prepare_fans(); user_mcode_ptrs_t previous = grbl.user_mcode; claims_ok = false; fans_init();
 CHECK(registered_settings); registered_settings->load(); CHECK(warnings == 1);
 CHECK(grbl.user_mcode.check == previous.check && grbl.user_mcode.execute == previous.execute);
 CHECK(output_calls == 0 && !fan_get_state(0) && !fan_get_state(1)); return 0;
}
