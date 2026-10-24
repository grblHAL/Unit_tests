#include "servo_host.h"
static char output[128];
static void write_output(const char *text) { CHECK(strlen(text) < sizeof(output)); strcpy(output, text); }
int main(void)
{
 prepare_servos(false, false); hal.stream.write = write_output;
 parser_block_t block = {0}; block.user_mcode = PWMServo_SetPosition; block.words.s = On; block.values.s = 60;
 grbl.user_mcode.execute(STATE_IDLE, &block); block.words.s = Off; grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(strstr(output, "Servo 0 position: 60.00 degrees") != NULL);
 block.user_mcode = (user_mcode_t)999;
 CHECK(grbl.user_mcode.check(block.user_mcode) == UserMCode_Normal);
 CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueOutOfRange); grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(previous_checks == 1 && previous_validations == 1 && previous_executions == 1);
 grbl.on_report_options(false); CHECK(strcmp(reported_plugin, "PWM servo") == 0); return 0;
}
