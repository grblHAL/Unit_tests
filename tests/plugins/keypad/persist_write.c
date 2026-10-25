#include "key_host.h"
int main(void)
{
    key_prepare();
    key_load();
    key_setting(Setting_JogStepSpeed, 240);
    key_setting(Setting_JogStepDistance, 0.5f);
    key_settings->save();
    FILE *f = fopen("key.nvs", "wb");
    CHECK(f && fwrite(key_memory, 1, sizeof(key_memory), f) == sizeof(key_memory));
    CHECK(fclose(f) == 0);
    return 0;
}
