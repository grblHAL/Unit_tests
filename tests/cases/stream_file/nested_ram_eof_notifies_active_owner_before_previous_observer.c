#include "support/nested_ram_stream_host.h"
int main(void)
{
    prepare_nested_ram_streams();
    for(int level = 2; level >= 0; level--) {
        CHECK(grbl.on_file_end(hal.stream.file, Status_OK) == Status_OK);
        CHECK(nested_local_order[level] + 1 == nested_prior_order);
        for(int i = 0; i < 3; i++) CHECK(nested_eof_calls[i] == (unsigned)(i >= level));
        close_nested_ram_level((unsigned)level);
    }
    CHECK(nested_prior_eof_calls == 3);
    return EXIT_SUCCESS;
}
