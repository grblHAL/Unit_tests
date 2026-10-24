#include "servo_host.h"
int main(void)
{
 prepare_servos(false, false);
 CHECK(servo_configs == 2 && servo_descriptions == 2);
 parser_block_t block = {0}; block.user_mcode = PWMServo_SetPosition;
 block.words.p = block.words.s = On; block.values.p = 1; block.values.s = 135;
 parser_block_t validated = block; CHECK(grbl.user_mcode.validate(&validated) == Status_OK);
 CHECK(!validated.words.s && !validated.words.p);
 grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(angles[0] == 0 && angles[1] == 135);
 return 0;
}
