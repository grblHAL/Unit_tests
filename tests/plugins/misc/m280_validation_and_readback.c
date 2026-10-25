#include "servo_host.h"
static char output[128];
static void write_output(const char *text) { CHECK(strlen(text) < sizeof(output)); strcpy(output, text); }
int main(void)
{
 prepare_servos(false, true); hal.stream.write = write_output;
 parser_block_t block = {0}; block.user_mcode = PWMServo_SetPosition; block.words.p = On; block.values.p = 0.5f;
 CHECK(grbl.user_mcode.validate(&block) == Status_BadNumberFormat);
 block = (parser_block_t){0}; block.user_mcode = PWMServo_SetPosition; block.words.s = On; block.values.s = 181;
 CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueOutOfRange);
 block = (parser_block_t){0}; block.user_mcode = PWMServo_SetPosition; block.words.p = On; block.values.p = 1;
 angles[1] = 72.5f; grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(strstr(output, "Servo 1 position: 72.50 degrees") != NULL);
 return 0;
}
