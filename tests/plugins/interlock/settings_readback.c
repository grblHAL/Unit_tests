#include "interlock_host.h"
int main(void)
{
    il_start();
    for (unsigned i = 0; i < 4; i++)
    {
        CHECK(il_read_float(900 + i) == -1 && il_read_float(912 + i) == -1 &&
              il_read_int(904 + i) == 0 && il_read_int(908 + i) == 1);
        CHECK(il_float(900 + i, i) == Status_OK && il_float(912 + i, 3 - i) == Status_OK);
        il_int(904 + i, i & 1);
        il_int(908 + i, (i + 1) & 1);
    }
    registered_settings->save();
    for (unsigned i = 0; i < 4; i++)
    {
        CHECK(il_float(900 + i, -1) == Status_OK && il_float(912 + i, -1) == Status_OK);
        il_int(904 + i, 0);
        il_int(908 + i, 1);
    }
    registered_settings->load();
    for (unsigned i = 0; i < 4; i++)
        CHECK(il_read_float(900 + i) == (float)i && il_read_float(912 + i) == (float)(3 - i) &&
              il_read_int(904 + i) == (i & 1) && il_read_int(908 + i) == ((i + 1) & 1));
    CHECK(saves == 2 && resets == 0 && warnings == 0);
    return 0;
}
