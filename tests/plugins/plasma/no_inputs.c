#include "plasma_host.h"
int main(void)
{
    plasma_prepare(0, true);
    plasma_init();
    CHECK(!plasma_details && plasma_warnings == 1);
    return 0;
}
