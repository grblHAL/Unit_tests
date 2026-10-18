#include "support/nested_ram_stream_host.h"
int main(void)
{
    prepare_nested_ram_streams();
    for(int level = 2; level >= 0; level--) {
        CHECK(grbl.report.status_message(Status_UserException) == Status_OK);
        for(int i = 0; i < 3; i++) CHECK(nested_status_calls[i] == (unsigned)(i >= level));
        close_nested_ram_level((unsigned)level);
    }
    CHECK(grbl.report.status_message(Status_UserException) == Status_UserException);
    for(unsigned i = 0; i < 3; i++) CHECK(nested_status_calls[i] == 1);
    return EXIT_SUCCESS;
}
