#include "hal.h"
#include "check.h"
#include <string.h>
int main(void)
{
    pin_cap_t cap = {.analog = true, .servo_pwm = true, .resolution = Resolution_12bit};
    CHECK(strcmp(xbar_resolution_to_string(cap), "?") == 0);
    return EXIT_SUCCESS;
}
