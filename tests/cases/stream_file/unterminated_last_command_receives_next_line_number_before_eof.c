#include "support/file_stream_host.h"
int main(void)
{
    prepare_file_stream("G90\nG91");
    vfs_file_t *file = stream_redirect_read("/fixture/program", NULL, NULL);
    CHECK(file != NULL);
    line_number_t final_number = 0;
    for(unsigned line = 0; line < 2; line++) {
        char block[8]; size_t used = 0; int32_t c;
        while((c = hal.stream.read()) != ASCII_LF) {
            CHECK(c >= 0 && c != ASCII_EOF && used + 1 < sizeof(block));
            block[used++] = (char)c;
        }
        block[used] = '\0';
        CHECK(gc_execute_block(block) == Status_OK);
        if(line == 0) CHECK(gc_state.line_number == 1);
        else final_number = gc_state.line_number;
    }
    CHECK(gc_state.modal.distance_incremental);
    CHECK(hal.stream.read() == ASCII_EOF);
    stream_redirect_close(file);
    CHECK(file_closes == 1 && !stream_is_file());
    fprintf(stderr, "Unterminated second command line=%lu expected=2\n", (unsigned long)final_number);
    CHECK(final_number == 2);
    return EXIT_SUCCESS;
}
