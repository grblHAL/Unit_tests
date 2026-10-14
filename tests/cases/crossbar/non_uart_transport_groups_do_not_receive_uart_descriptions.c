#include "hal.h"
#include "check.h"
#include <string.h>
int main(void)
{
    CHECK(xbar_group_to_description(PinGroup_SPI) == NULL);
    CHECK(xbar_group_to_description(PinGroup_CAN) == NULL);
    CHECK(xbar_group_to_description(PinGroup_USB) == NULL);
    CHECK(strcmp(xbar_group_to_description(PinGroup_UART2), "UART2") == 0);
    CHECK(strcmp(xbar_group_to_description(PinGroup_UART3), "UART3") == 0);
    return EXIT_SUCCESS;
}
