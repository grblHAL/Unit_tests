#include "support/plugin_numeric_settings_host.h"
int main(void)
{
    check_numeric_storage(4, "4294967295", 4294967295u);
    return EXIT_SUCCESS;
}
