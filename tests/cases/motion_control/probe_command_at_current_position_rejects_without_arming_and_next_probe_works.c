#include "support/probe_command_rejection_host.h"
int main(void)
{
    reject_probe_then_measure_contact("G38.2X0F100", Status_GcodeInvalidTarget);
    return EXIT_SUCCESS;
}
