#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_STA);
    at_setting_string(Setting_WiFi_STA_SSID, "changed");
    at_settings->load();
    CHECK(!strcmp(at_setting(Setting_WiFi_STA_SSID)->value, "Shop"));
    const setting_detail_t *setting = at_setting(Setting_IpAddress3);
    CHECK(setting->datatype == Format_IPv4 && setting->type == Setting_NonCoreFn);
    CHECK(!strcmp(((setting_get_string_ptr)setting->get_value)(setting->id), "192.168.5.1"));
    at_settings->save();
    at_settings->load();
    at_start();
    CHECK(at_command_seen("AT+CWJAP=\"Shop\",\"fixturepass\"\n") &&
          at_command_seen("AT+CIPSERVER=1,23\n"));
    return 0;
}
