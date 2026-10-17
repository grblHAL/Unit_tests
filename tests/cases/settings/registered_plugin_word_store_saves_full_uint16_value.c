#include "support/plugin_numeric_settings_host.h"
int main(void)
{
    check_numeric_storage(3, "65535", 65535u);
    return EXIT_SUCCESS;
}
