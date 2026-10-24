#include "rgb_host.h"
int main(void)
{
 prepare_hooks(); user_mcode_ptrs_t previous = grbl.user_mcode; rgb_led_init();
 CHECK(grbl.user_mcode.check == previous.check && grbl.user_mcode.validate == previous.validate && grbl.user_mcode.execute == previous.execute);
 grbl.on_report_options(false); CHECK(previous_reports == 1 && plugin_reports == 1);
 CHECK(strcmp(reported_plugin, "RGB LED strips (N/A)") == 0);
 return 0;
}
