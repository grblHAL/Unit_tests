#include "support/nested_ram_stream_host.h"
int main(void)
{
    prepare_nested_ram_streams();
    for(unsigned remaining = 3; remaining; remaining--) {
        unsigned owner = remaining - 1;
        report_init_fns();
        report_init_fns();
        CHECK(grbl.report.status_message(Status_UserException) == Status_OK);
        CHECK(nested_status_calls[owner] == 1);
        for(unsigned i = 0; i < owner; i++) CHECK(nested_status_calls[i] == 0);
        close_nested_ram_level(owner);
    }
    size_t before = strlen(engine_output);
    CHECK(grbl.report.status_message(Status_UserException) == Status_UserException);
    CHECK(strlen(engine_output) > before);
    return EXIT_SUCCESS;
}
