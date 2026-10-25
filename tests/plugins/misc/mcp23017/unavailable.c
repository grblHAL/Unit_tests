#include "mcp_host.h"
int main(void)
{
#ifdef MCP_NO_BUS
    bus_ok = false;
#else
    probe_ok = false;
#endif
    start_mcp();
    CHECK(starts == 1 && writes == 0 && registrations == 0);
#ifdef MCP_NO_BUS
    CHECK(probes == 0);
#else
    CHECK(probes == 1);
#endif
    return 0;
}
