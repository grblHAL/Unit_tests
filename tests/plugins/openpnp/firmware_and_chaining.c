#include "openpnp_host.h"
int main(void)
{
 prepare_openpnp(); parser_block_t block = {0}; block.user_mcode = OpenPNP_FirmwareInfo;
 CHECK(grbl.user_mcode.check(block.user_mcode) == UserMCode_Normal); CHECK(grbl.user_mcode.validate(&block) == Status_OK);
 grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(strstr(pnp_output, "FIRMWARE_NAME:grblHAL") != NULL && strstr(pnp_output, "FIRMWARE_VERSION:" GRBL_VERSION) != NULL);
 CHECK(strstr(pnp_output, "FIRMWARE_BUILD:") != NULL);
 block.user_mcode = (user_mcode_t)999; CHECK(grbl.user_mcode.check(block.user_mcode) == UserMCode_Normal);
 CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueOutOfRange); grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(previous_checks == 1 && previous_validations == 1 && previous_executions == 1);
 grbl.on_report_options(false); CHECK(plugin_reports == 1 && previous_reports == 1 && strcmp(reported_plugin, "OpenPNP") == 0);
 return 0;
}
