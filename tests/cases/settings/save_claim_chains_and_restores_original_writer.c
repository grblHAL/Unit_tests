#include "support/settings_host.h"
#include "check.h"
static driver_settings_save_ptr original_save;
static unsigned save_calls;
static void chained_save(void) { save_calls++; original_save(); }

int main(void)
{
    prepare_settings_store();
    original_save = settings_claim_save(chained_save);
    CHECK(original_save != NULL);
    CHECK(settings_claim_save(NULL) == chained_save);
    settings_write_global();
    CHECK(save_calls == 1);
    CHECK(settings_claim_save(original_save) == chained_save);
    settings_write_global();
    CHECK(save_calls == 1);
    CHECK(settings_claim_save(NULL) == original_save);
    return EXIT_SUCCESS;
}
