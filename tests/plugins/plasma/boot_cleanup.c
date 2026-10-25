#include "plasma_host.h"
int main(void)
{
    CHECK(!remove("plasma.nvs"));
    return 0;
}
