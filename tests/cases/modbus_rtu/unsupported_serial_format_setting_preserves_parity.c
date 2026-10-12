#include "support/rtu_host.h"
#include "system.h"

int main(void)
{
    prepare_rtu();
    CHECK(modbus_get_rtu_stream()->set_format == NULL);
    char parity[] = "1";
    CHECK(settings_store_setting(Setting_ModBus_StreamFormat, parity) == Status_SettingDisabled);
    CHECK(settings.modbus_stream_format.parity == Serial_ParityNone);
    return EXIT_SUCCESS;
}
