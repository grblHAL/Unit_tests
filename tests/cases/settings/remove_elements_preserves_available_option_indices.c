#include "support/settings_elements_host.h"
#include "check.h"

int main(void)
{
    prepare_setting_elements("First,Second,Third");
    setting_remove_elements((setting_id_t)1001, 5, false);
    CHECK(strcmp(element_format, "First,N/A,Third") == 0);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
