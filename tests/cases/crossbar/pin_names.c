#include <string.h>
#include "hal.h"
#include "check.h"

int main(void)
{
    CHECK(strcmp(xbar_fn_to_pinname(Input_Probe), "Probe") == 0);
    CHECK(strcmp(xbar_fn_to_pinname(Input_LimitX), "X limit min") == 0);
    CHECK(strcmp(xbar_fn_to_pinname((pin_function_t)65535), "N/A") == 0);
    return EXIT_SUCCESS;
}
