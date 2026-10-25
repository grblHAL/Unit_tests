#include "select_host.h"
int main(void)
{
    select_prepare();
    CHECK(select_binding(1, 2) == Status_OK && select_tool_start(1, 10) == Status_OK);
    select_settings->save();
    FILE *f = fopen("select-eeprom.bin", "wb");
    CHECK(f && fwrite(memory, 1, sizeof(memory), f) == sizeof(memory));
    CHECK(fclose(f) == 0);
    return 0;
}
