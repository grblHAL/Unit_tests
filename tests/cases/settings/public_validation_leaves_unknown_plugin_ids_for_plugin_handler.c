#include "support/settings_validation_host.h"

int main(void)
{
    prepare_settings_store();
    char value[] = "123";
    CHECK(setting_get_details((setting_id_t)65535, NULL) == NULL);
    CHECK(setting_validate((setting_id_t)65535, 123, value) == Status_OK);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
