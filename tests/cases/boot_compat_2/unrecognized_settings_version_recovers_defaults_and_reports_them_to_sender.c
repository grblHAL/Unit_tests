#include "support/boot_legacy_default_recovery_host.h"
int main(void)
{
    boot_with_unrecognized_saved_version();
    return EXIT_SUCCESS;
}
