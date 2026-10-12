#include "support/stream_connection_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_connections();
    sys.driver_started = true;
    CHECK(stream_connect(&secondary_connection));
    CHECK(strstr(secondary_output, "GrblHAL " GRBL_VERSION) != NULL);
    CHECK(strstr(primary_output, "TELNET STREAM ACTIVE") != NULL);
    return EXIT_SUCCESS;
}
