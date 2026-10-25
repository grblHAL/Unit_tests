#include "lfs_failure_host.h"
int main(void)
{
 const struct lfs_config *config = eeprom_littlefs_hal(); uint8_t buffer[8] = {0};
 int result = config->read(config, 0, 0, buffer, sizeof(buffer));
 CHECK(lfs_reads == 1 && lfs_writes == 0); CHECK(result == LFS_ERR_IO); return 0;
}
