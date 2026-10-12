#include "support/file_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_file_stream("G0X1");
    CHECK(stream_redirect_read("/fixture/missing", NULL, NULL) == NULL);
    CHECK(hal.stream.read == stream_get_null);
    CHECK(hal.stream.file == NULL);
    return EXIT_SUCCESS;
}
