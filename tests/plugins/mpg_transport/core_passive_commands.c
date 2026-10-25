#include "mpg_host.h"
#if MPG_TRANSPORT_DEFAULT_TRANSPORT == 1
static uint8_t sequence;
#endif
static void receive(const char *text)
{
#if MPG_TRANSPORT_DEFAULT_TRANSPORT == 0
    mpg_bytes((const uint8_t *)text, strlen(text));
#else
    mpg_receive(++sequence, MpgFrame_Dat, (const uint8_t *)text, strlen(text));
#endif
}
static void expect_output(const char *expected)
{
    mpg_core_run();
    mpg_poll();
    char actual[256] = {0};
    size_t used = 0;
    for (unsigned i = 0; i < packets; i++)
    {
        CHECK(i < 32);
#if MPG_TRANSPORT_DEFAULT_TRANSPORT == 0
        size_t size = sent[i].size;
        const uint8_t *data = sent[i].data;
#else
        CHECK(sent[i].size >= MPG_TRANSPORT_OVERHEAD);
        if (sent[i].data[2] == MpgFrame_Ack)
            continue;
        CHECK(sent[i].data[2] == MpgFrame_Dat);
        size_t size = sent[i].data[3];
        CHECK(sent[i].size == size + MPG_TRANSPORT_OVERHEAD);
        const uint8_t *data = sent[i].data + 4;
#endif
        CHECK(used + size < sizeof(actual));
        memcpy(actual + used, data, size);
        used += size;
#if MPG_TRANSPORT_DEFAULT_TRANSPORT == 1
        mpg_ack(i);
#endif
    }
    CHECK(strcmp(actual, expected) == 0 && proxy.get_tx_buffer_count() == 0 &&
          proxy.get_rx_buffer_count() == 0 && !sys.mpg_mode && output[0] == 0);
    packets = 0;
}
int main(void)
{
    mpg_core_start();
    receive("$");
    mpg_core_run();
    CHECK(command_calls == 0 && packets == 0);
    receive("!I\r");
    expect_output("[host-command]" ASCII_EOL "ok" ASCII_EOL);
    CHECK(command_calls == 1 && strcmp(last_command, "$I") == 0);
    receive("\n");
    expect_output("");
    CHECK(command_calls == 1);
    receive("G1X1\n");
    char error[32];
    snprintf(error, sizeof(error), "error:%u%s", (unsigned)Status_AccessDenied, ASCII_EOL);
    expect_output(error);
    CHECK(command_calls == 1);
    command_status = Status_SettingDisabled;
    receive("$I\n");
    snprintf(error, sizeof(error), "[host-command]%serror:%u%s", ASCII_EOL,
             (unsigned)Status_SettingDisabled, ASCII_EOL);
    expect_output(error);
    CHECK(command_calls == 2 && strcmp(last_command, "$I") == 0);
    receive("\n");
    expect_output("ok" ASCII_EOL);
    CHECK(command_calls == 2);
    command_status = Status_OK;
    receive("$I\n");
    expect_output("[host-command]" ASCII_EOL "ok" ASCII_EOL);
    CHECK(command_calls == 3 && rt_calls > 0);
    return 0;
}
