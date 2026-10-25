#include "bt_host.h"
int main(void)
{
    CHECK(!remove("bluetooth.nvs"));
    return 0;
}
