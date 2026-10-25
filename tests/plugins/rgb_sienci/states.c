#include "rgb_host.h"
int main(void)
{
    rgb_start();
    hal.rgb0.num_devices = 8;
    sys_state_t states[] = {STATE_CYCLE,       STATE_JOG,   STATE_HOMING, STATE_HOLD,
                            STATE_SAFETY_DOOR, STATE_ALARM, STATE_ESTOP,  STATE_TOOL_CHANGE,
                            STATE_SLEEP,       STATE_IDLE};
    unsigned colors[][3] = {{0, 255, 0},     {0, 255, 0},    {0, 0, 255}, {255, 255, 0},
                            {255, 255, 0},   {255, 0, 0},    {255, 0, 0}, {255, 0, 255},
                            {127, 127, 127}, {255, 255, 255}};
    for (unsigned i = 0; i < 10; i++)
    {
        rgb_state(states[i]);
        rgb_expect(0, colors[i][0], colors[i][1], colors[i][2]);
    }
    rgb_state(STATE_CHECK_MODE);
#if STATUS_LIGHT_ENABLE == 2
    rgb_expect(0, 0, 0, 255);
#else
    rgb_expect(0, 0, 255, 255);
#endif

    return 0;
}
