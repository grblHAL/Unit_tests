#include "support/probe_command_rejection_host.h"
int main(void)
{
    reject_probe_then_measure_contact("G38.2F100", Status_GcodeNoAxisWords);
    return EXIT_SUCCESS;
}
