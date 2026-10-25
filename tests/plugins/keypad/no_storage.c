#include "key_host.h"
int main(void)
{
    key_prepare();
    key_storage_ok = false;
    CHECK(!keypad_init() && !key_settings);
    return 0;
}
