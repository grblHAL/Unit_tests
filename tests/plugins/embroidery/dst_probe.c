#include "embroidery_host.h"
int main(void)
{
    memcpy(pattern, "#PES0001", 8);
    pattern_mount(12);
    CHECK(!tajima_open_file(pattern_file, &pattern_api) && vfs_tell(pattern_file) == 0 &&
          !pattern_api.get_stitch);
    pattern_close();
    return 0;
}
