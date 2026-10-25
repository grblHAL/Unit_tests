#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
#if TEST_MODVFD
    vfd_word(Setting_VFD_11, 0x1234);
    vfd_float(Setting_VFD_16, 2);
    vfd_float(Setting_VFD_17, 3);
#else
    vfd_word(Setting_VFD_RPM_Hz, 120);
#endif
    vfd_settings->save();
    FILE *file = fopen("vfd.nvs", "wb");
    CHECK(file);
    CHECK(fwrite(memory, 1, 16384, file) == 16384);
    CHECK(fclose(file) == 0);
    return 0;
}
