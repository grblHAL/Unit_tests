#include "support/boot_legacy_default_recovery_host.h"
int main(void)
{
    boot_with_corrupt_saved_checksum();
    return EXIT_SUCCESS;
}
