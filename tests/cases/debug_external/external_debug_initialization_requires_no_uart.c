#include "support/debug_external_host.h"
int main(void)
{
    engine_prepare();
    CHECK(debug_stream_init());
    CHECK(external_write_calls == 0);
    CHECK(engine_output[0] == 0);
    return 0;
}
