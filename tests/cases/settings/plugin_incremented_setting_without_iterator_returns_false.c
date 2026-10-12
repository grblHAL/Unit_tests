#include "support/settings_registry_host.h"
#include "check.h"
static bool unexpected_callback(const setting_detail_t *setting, uint_fast16_t offset, void *data) { (void)setting; (void)offset; (void)data; CHECK(false); return true; }
int main(void)
{
    prepare_settings_registry();
    CHECK(!settings_iterator(&registry_setting[0], unexpected_callback, NULL));
    return EXIT_SUCCESS;
}
