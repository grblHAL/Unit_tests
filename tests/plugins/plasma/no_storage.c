#include "plasma_host.h"
int main(void)
{
    plasma_prepare(3, true);
    plasma_storage_ok = false;
    plasma_init();
    CHECK(!plasma_details && plasma_warnings == 1);
    return 0;
}
