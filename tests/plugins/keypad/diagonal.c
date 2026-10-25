#include "key_host.h"
int main(void)
{
    key_prepare();
    key_load();
    key_press('2');
    const char keys[] = {'r', 'q', 's', 't', 'w', 'v', 'u', 'x'};
    const char *axes[] = {"X0.250Y0.250", "X0.250Y-0.250", "X-0.250Y0.250", "X-0.250Y-0.250",
                          "X0.250Z0.250", "X0.250Z-0.250", "X-0.250Z0.250", "X-0.250Z-0.250"};
    for (unsigned i = 0; i < 8; i++)
    {
        key_press(keys[i]);
        char expected[64];
        snprintf(expected, sizeof(expected), "$J=G91G21%sF100.", axes[i]);
        fprintf(stderr, "jog=%s\n", key_gcode);
        CHECK(!strcmp(key_gcode, expected));
        key_release();
    }
    return 0;
}
