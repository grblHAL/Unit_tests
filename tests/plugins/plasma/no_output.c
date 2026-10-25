#include "plasma_host.h"
int main(void)
{
    plasma_prepare(3, false);
    plasma_init();
    CHECK(!plasma_details && plasma_warnings == 1);
    return 0;
}
