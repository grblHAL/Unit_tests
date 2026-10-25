#include "nowforever_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_clear_requests();
    vfd_motor->update_rpm(vfd_motor, 30);
    expect_write(0, 0x901, 100, false);
    vfd_motor->update_rpm(vfd_motor, 30000);
    expect_write(1, 0x901, 40000, false);
    vfd_motor->update_rpm(vfd_motor, 30000);
    CHECK(vfd_requests == 2);
    return 0;
}
