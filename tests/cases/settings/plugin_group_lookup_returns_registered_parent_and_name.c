#include "support/settings_registry_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_registry();
    const setting_group_detail_t *group = setting_get_group_details((setting_group_t)1000);
    CHECK(group == &registry_groups[0]);
    CHECK(group->parent == Group_General);
    CHECK(strcmp(group->name, "Channels") == 0);
    CHECK(settings_is_group_available((setting_group_t)1000));
    CHECK(setting_get_group_details((setting_group_t)65530) == NULL);
    return EXIT_SUCCESS;
}
