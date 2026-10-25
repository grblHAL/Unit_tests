#include "coolant_host.h"
int main(void)
{
    coolant_storage = false;
    coolant_prepare(true);
    CHECK(!coolant_settings && coolant_warnings == 1);
    return 0;
}
