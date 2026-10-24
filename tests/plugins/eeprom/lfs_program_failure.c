#include "lfs_failure_host.h"
int main(void)
{
 const struct lfs_config *config = eeprom_littlefs_hal(); const uint8_t buffer[256] = {1};
 int result = config->prog(config, 0, 0, buffer, sizeof(buffer));
 CHECK(lfs_writes == 1 && lfs_reads == 0); CHECK(result == LFS_ERR_IO); return 0;
}
