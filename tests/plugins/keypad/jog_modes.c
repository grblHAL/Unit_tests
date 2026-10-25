#include "key_host.h"
int main(void)
{
    key_prepare();
    key_load();
    key_press('R');
    fprintf(stderr, "jog=%s\n", key_gcode);
    CHECK(!strcmp(key_gcode, "$J=G91G21X3000.F3000."));
    key_release();
    CHECK(key_realtime_count == 1 && key_realtime[0] == CMD_JOG_CANCEL);
    key_press('1');
    key_press('m');
    key_press('B');
    fprintf(stderr, "jog=%s\n", key_gcode);
    CHECK(!strcmp(key_gcode, "$J=G91G21Y-500.F60."));
    key_release();
    key_press('2');
    key_press('U');
    fprintf(stderr, "jog=%s\n", key_gcode);
    CHECK(!strcmp(key_gcode, "$J=G91G21Z0.025F100."));
    key_release();
    CHECK(key_gcodes == 3);
    return 0;
}
