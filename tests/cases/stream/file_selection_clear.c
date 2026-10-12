#include "support/engine_host.h"
#include "stream.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    vfs_file_t file = {0};
    stream_set_file(&file, stream_get_null);
    CHECK(stream_is_file());
    CHECK(hal.stream.read == stream_get_null);
    gc_state.file_stream = true;
    stream_set_file(NULL, NULL);
    CHECK(!stream_is_file());
    CHECK(!gc_state.file_stream);
    CHECK(hal.stream.read == stream_get_null);
    return EXIT_SUCCESS;
}
