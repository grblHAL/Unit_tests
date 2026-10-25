#include "bltouch_host.h"
#include <string.h>
static void option(char word, float value)
{
    parser_block_t block = {0};
    block.user_mcode = Probe_Deploy;
    if (word == 'S')
    {
        block.words.s = On;
        block.values.s = value;
    }
    else
    {
        block.words.d = On;
        block.values.d = value;
    }
    CHECK(dispatch_bltouch(&block) == Status_OK);
}
int main(void)
{
    load_bltouch();
    float target[N_AXIS] = {0};
    plan_line_data_t data = {0};
    option('S', 1);
    CHECK(grbl.on_probe_start((axes_signals_t){.mask = 4}, target, &data));
    CHECK(angle == 90 && outputs == 1);
    option('S', 0);
    CHECK(grbl.on_probe_start((axes_signals_t){.mask = 4}, target, &data));
    CHECK(angle == 10 && outputs == 2);
    grbl.on_probe_completed();
    CHECK(angle == 90);
    option('D', 0);
    unsigned before = outputs;
    CHECK(grbl.on_probe_start((axes_signals_t){.mask = 4}, target, &data));
    CHECK(angle == 90 && outputs == before);
    option('D', 1);
    CHECK(grbl.on_probe_start((axes_signals_t){.mask = 4}, target, &data));
    CHECK(angle == 10 && outputs == before + 1);
    parser_block_t report = {0};
    report.user_mcode = Probe_Deploy;
    report.words.h = On;
    before = outputs;
    CHECK(dispatch_bltouch(&report) == Status_OK);
    CHECK(strstr(bltouch_output, "[PROBE HS:0]") && outputs == before);
    return 0;
}
