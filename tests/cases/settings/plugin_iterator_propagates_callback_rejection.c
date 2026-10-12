#include "support/settings_registry_host.h"
#include "check.h"
static unsigned calls, iterator_calls;
static bool record_plugin(const setting_detail_t *setting, uint_fast16_t offset, void *data) { CHECK(setting == &registry_setting[0]); CHECK(data == &calls); CHECK(offset == 2 * calls); calls++; return calls != 2; }
static bool plugin_iterate(const setting_detail_t *setting, setting_output_ptr callback, void *data) { CHECK(setting == &registry_setting[0]); iterator_calls++; for(unsigned i=0; i<3; i++) if(!callback(setting, 2*i, data)) return false; return true; }
int main(void)
{
    registry_details.iterator = plugin_iterate;
    prepare_settings_registry();
    CHECK(!settings_iterator(&registry_setting[0], record_plugin, &calls));
    CHECK(iterator_calls == 1);
    CHECK(calls == 2);
    return EXIT_SUCCESS;
}
