#include "support/system_metadata_host.h"
static unsigned encoder_calls;
static spindle_data_t data;
static spindle_data_t *get_encoder(spindle_data_request_t request)
{
    (void)request;
    encoder_calls++;
    return &data;
}
static void reset_encoder(void) { encoder_calls++; }
int main(void)
{
    prepare_system_metadata();
    spindle_ptrs_t *spindle = gc_spindle_get(0)->hal;
    spindle->get_data = NULL;
    spindle->reset_data = NULL;
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$SD - output spindle encoder data") == NULL);
    CHECK(strstr(metadata_output, "$SR - reset spindle encoder data") == NULL);
    metadata_output[0] = 0;
    spindle->get_data = get_encoder;
    spindle->reset_data = reset_encoder;
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$SD - output spindle encoder data") != NULL);
    CHECK(strstr(metadata_output, "$SR - reset spindle encoder data") != NULL);
    CHECK(encoder_calls == 0);
    return EXIT_SUCCESS;
}
