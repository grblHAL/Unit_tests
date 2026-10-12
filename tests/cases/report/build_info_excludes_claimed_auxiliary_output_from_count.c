#include "support/build_report_host.h"
#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    register_ioports();
    uint8_t port = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &port, "relay") != NULL);
    build_report(true);
    CHECK(strstr(engine_output, "[AUX IO:2,1,0,0]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
