#include "at_host.h"
#include "eeprom_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_AP);
    memory[2048] ^= 1;
    at_settings->load();
    CHECK(*(grbl_wifi_mode_t *)at_setting(Setting_WifiMode)->value == WiFiMode_STA);
    CHECK(!*(char *)at_setting(Setting_WiFi_STA_SSID)->value);
    CHECK(!strcmp(at_setting(Setting_WiFi_AP_SSID)->value, "grblHAL_AP"));
    at_setting_string(Setting_WiFi_STA_SSID, "Shop");
    at_setting_string(Setting_WiFi_STA_Password, "fixturepass");
    at_settings->save();
    at_start();
    CHECK(at_command_seen("AT+CIPSERVER=1,23\n") && !at_warnings);
    return 0;
}
