#include "support/engine_host.h"
#include "stream.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    const io_stream_t *stream = stream_null_init(115200);
    CHECK(stream != NULL);
    CHECK(stream->type == StreamType_Null);
    CHECK(stream->read() == SERIAL_NO_DATA);
    CHECK(stream_get_null() == SERIAL_NO_DATA);
    return EXIT_SUCCESS;
}
