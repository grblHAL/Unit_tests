#include "support/boot_host.h"

static unsigned mpg_registration_calls;
static int32_t pendant_read(void) { return SERIAL_NO_DATA; }
static bool pendant_rx(bool disabled) { (void)disabled; return true; }
static const io_stream_t pendant = {.type = StreamType_Serial, .instance = 1,
    .read = pendant_read, .disable_rx = pendant_rx};
static void registered(io_stream_t *stream, bool tx_capable)
{
    CHECK(stream->read == pendant_read && !tx_capable);
    mpg_registration_calls++;
}
static void register_driver_pendant(void)
{
    grbl.on_mpg_registered = registered;
    CHECK(stream_mpg_register(&pendant, true, NULL));
    hal.driver_cap.mpg_mode = true;
}
int main(void)
{
    boot_during_init = register_driver_pendant;
    CHECK(grbl_enter() == 0);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(mpg_registration_calls == 1 && !sys.mpg_mode);
    CHECK(hal.stream.read == read_char && boot_reads == strlen(boot_program));
    const char *status = strstr(engine_output, "<Idle|");
    CHECK(status != NULL && strstr(status, "|WPos:0.000,0.000,0.000|") != NULL);
    CHECK(strstr(status + 1, "<Idle|") == NULL);
    CHECK(strstr(engine_output, "[GC:") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
