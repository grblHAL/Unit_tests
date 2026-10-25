#include "fan_host.h"
int main(void)
{
 prepare_fans(); user_mcode_ptrs_t previous = grbl.user_mcode;
 available_ports = 0; fans_init(); CHECK(warnings == 1 && registered_settings == NULL);
 available_ports = 2; alloc_ok = false; fans_init(); CHECK(warnings == 2 && registered_settings == NULL);
 CHECK(grbl.user_mcode.check == previous.check && grbl.user_mcode.execute == previous.execute);
 CHECK(output_calls == 0); return 0;
}
