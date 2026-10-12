#include "support/settings_elements_host.h"
#include "check.h"

int main(void)
{
    prepare_setting_elements("First,Second,Third");
    setting_remove_elements((setting_id_t)65530, 0, true);
    CHECK(strcmp(element_format, "First,Second,Third") == 0);
    return EXIT_SUCCESS;
}
