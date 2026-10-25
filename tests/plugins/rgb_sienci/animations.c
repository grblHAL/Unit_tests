#include "rgb_host.h"
int main(void)
{
    rgb_start();
    sys_state_t states[] = {STATE_ALARM, STATE_JOG,         STATE_HOMING,     STATE_TOOL_CHANGE,
                            STATE_HOLD,  STATE_SAFETY_DOOR, STATE_CHECK_MODE, STATE_ESTOP};
    unsigned colors[][3] = {{255, 0, 0},   {0, 255, 0},   {0, 0, 255},   {255, 0, 255},
                            {255, 255, 0}, {255, 255, 0}, {0, 255, 255}, {255, 0, 0}};
    for (unsigned s = 0; s < 8; s++)
    {
        rgb_state(states[s]);
        CHECK(pending);
        for (unsigned frame = 0; frame < 4; frame++)
        {
            rgb_run_next();
            CHECK(pixels[0][12].R == colors[s][0] && pixels[0][12].G == colors[s][1] &&
                  pixels[0][12].B == colors[s][2]);
        }
    }
    rgb_state(STATE_IDLE);
    while (pending)
        rgb_run_next();
    rgb_expect(0, 255, 255, 255);
    return 0;
}
