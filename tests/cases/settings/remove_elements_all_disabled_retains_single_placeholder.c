#include "support/settings_elements_host.h"
#include "check.h"

int main(void)
{
    prepare_setting_elements("First,Second,Third");
    setting_remove_elements((setting_id_t)1001, 0, true);
    CHECK(strcmp(element_format, "N/A") == 0);
    return EXIT_SUCCESS;
}
