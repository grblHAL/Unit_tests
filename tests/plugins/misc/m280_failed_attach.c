#include "servo_host.h"
int main(void)
{
 prepare_servos(true, false);
 CHECK(servo_configs == 2 && servo_descriptions == 0 && servo_outputs == 0);
 parser_block_t block = {0}; block.user_mcode = PWMServo_SetPosition; block.words.p = On;
 CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueOutOfRange);
 return 0;
}
