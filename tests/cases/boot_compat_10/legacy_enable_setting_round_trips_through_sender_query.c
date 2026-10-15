#include "support/boot_legacy_host.h"
#include "check.h"

int main(void)
{
    boot_program = "$4=0\n$4\n";
    run_legacy_boot_program();
    CHECK(settings.steppers.enable_invert.mask == AXES_BITMASK);
    if(strstr(engine_output, "$4=0" ASCII_EOL) == NULL)
        fprintf(stderr, "Sender output after $4=0 and query:\n%s", engine_output);
    CHECK(strstr(engine_output, "$4=0" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
