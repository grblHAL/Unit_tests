#include "fan_host.h"
int main(void)
{
 load_fans(); grbl.on_unknown_accessory_override(CMD_OVERRIDE_FAN0_TOGGLE); CHECK(outputs[0] && fan_get_state(0));
 grbl.on_report_options(false); CHECK(plugin_reports == 1 && strcmp(reported_plugin, "Fans") == 0);
 CHECK(strstr(fan_output, "[FANS:2]") != NULL);
 fan_output[0] = 0; grbl.on_realtime_report(hal.stream.write, (report_tracking_flags_t){.fan = On});
 CHECK(strcmp(fan_output, "|Fan:1") == 0);
 grbl.on_unknown_accessory_override(CMD_OVERRIDE_FAN0_TOGGLE); CHECK(!outputs[0]); return 0;
}
