#include <string.h>
#include "hal.h"
#include "check.h"

int main(void)
{
    pin_cap_t cap = {0}; CHECK(strcmp(xbar_resolution_to_string(cap), "?") == 0);
    cap.analog = 1; cap.resolution = Resolution_12bit; CHECK(strcmp(xbar_resolution_to_string(cap), "12") == 0);
    cap.resolution = Resolution_32bit; CHECK(strcmp(xbar_resolution_to_string(cap), "32") == 0);
    cap.pwm = 1; CHECK(strcmp(xbar_resolution_to_string(cap), "?") == 0);
    return EXIT_SUCCESS;
}
