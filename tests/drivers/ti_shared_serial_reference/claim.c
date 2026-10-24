#include "reference_host.h"
int main(void)
{
    CHECK(serialInit(9600) == NULL);
    uart_start();
    CHECK(reference_streams && reference_streams->streams[0].instance == 0 &&
          reference_streams->streams[0].flags.claimable &&
          reference_streams->streams[0].flags.claimed &&
          !reference_streams->streams[0].flags.can_set_baud);
    CHECK(serialInit(115200) == NULL && pins == 2 && clocks == 2);
    return 0;
}
