#include <string.h>
#include "hal.h"
#include "check.h"

int main(void)
{
    CHECK(strcmp(xbar_group_to_description(PinGroup_UART), "UART1") == 0);
    CHECK(strcmp(xbar_group_to_description(PinGroup_UART4), "UART4") == 0);
    CHECK(xbar_group_to_description(PinGroup_Home) == NULL);
    return EXIT_SUCCESS;
}
