#include "key_host.h"
int main(void)
{
    key_prepare();
    FILE *f = fopen("key.nvs", "rb");
    CHECK(f && fread(key_memory, 1, sizeof(key_memory), f) == sizeof(key_memory));
    CHECK(fclose(f) == 0);
    key_load();
    key_press('2');
    key_press('R');
    fprintf(stderr, "jog=%s\n", key_gcode);
    CHECK(!strcmp(key_gcode, "$J=G91G21X0.500F240."));
    key_release();
    CHECK(remove("key.nvs") == 0);
    return 0;
}
