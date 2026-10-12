#include "support/settings_elements_host.h"
#include "check.h"

int main(void)
{
    prepare_setting_elements("First,Second,Third");
    setting_remove_elements((setting_id_t)1001, 1, true);
    CHECK(strcmp(element_format, "First") == 0);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
