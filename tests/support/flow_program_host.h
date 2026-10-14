#pragma once
#include "support/flow_file_host.h"
/* Stream bytes and rewinds remain upstream-owned; feed normalized blocks to the
   public parser, as the protocol's ordinary line processing does. No motion. */
static inline status_code_t run_flow_program(const char *program)
{
    prepare_file_stream(program);
    ngc_flowctrl_init();
    CHECK(stream_redirect_read("/fixture/program", NULL, NULL) != NULL);
    char block[128];
    unsigned length = 0, reads = 0;
    status_code_t status = Status_OK;
    int32_t c;
    while(++reads < 10000) {
        c = hal.stream.read();
        if(c == SERIAL_NO_DATA) continue;
        if(c == ASCII_EOF) break;
        if(c == ASCII_LF) {
            block[length] = '\0';
            status = gc_execute_block(block);
            if(status != Status_OK) {
                fprintf(stderr, "Macro block returned status %u\n", (unsigned)status);
                break;
            }
            length = 0;
        } else {
            CHECK(length + 1 < sizeof(block));
            block[length++] = (char)c;
        }
    }
    bool within_read_bound = reads < 10000;
    ngc_flowctrl_init();
    stream_redirect_close(hal.stream.file);
    CHECK(file_closes == 1);
    CHECK(within_read_bound);
    return status;
}
static inline float flow_program_parameter(ngc_param_id_t id)
{
    float value;
    CHECK(ngc_param_get(id, &value));
    return value;
}
