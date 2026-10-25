#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    FILE *file = fopen("vfd.nvs", "rb");
    CHECK(file);
    CHECK(fread(memory, 1, 16384, file) == 16384);
    CHECK(fclose(file) == 0);
    vfd_start();
    vfd_motor->update_rpm(vfd_motor, 6000);
#if TEST_MODVFD
    vfd_expect(0, ModBus_WriteRegister, 0x1234, 4000, false);
#else
    vfd_expect(0, ModBus_WriteRegister, 0x2001, 5000, false);
#endif
    CHECK(remove("vfd.nvs") == 0);
    return 0;
}
