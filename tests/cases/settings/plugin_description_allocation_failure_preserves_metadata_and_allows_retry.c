#include "support/settings_registry_host.h"
#include "check.h"
void *__real_realloc(void *ptr, size_t size);
static bool reject_growth;
static unsigned rejected_growths;
void *__wrap_realloc(void *ptr, size_t size)
{
    if(reject_growth) {
        reject_growth = false;
        rejected_growths++;
        return NULL;
    }
    return __real_realloc(ptr, size);
}

int main(void)
{
    prepare_settings_registry();
    registry_setting[0].flags.subgroups = true;
    registry_value = 42;
    reject_growth = true;
    (void)setting_get_description((setting_id_t)1005);
    CHECK(rejected_growths == 1 && !reject_growth);
    CHECK(strcmp(registry_descriptions[0].description, "Channel ? calibration") == 0);
    CHECK(registry_value == 42 && change_callbacks == 0);
    CHECK(strcmp(setting_get_description((setting_id_t)1005), "Channel 3 calibration") == 0);
    CHECK(strcmp(setting_get_description((setting_id_t)1001), "Channel 1 calibration") == 0);
    CHECK(registry_value == 42 && change_callbacks == 0);
    return EXIT_SUCCESS;
}
