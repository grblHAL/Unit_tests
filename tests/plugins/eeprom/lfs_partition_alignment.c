#include "eeprom_host.h"
#include "littlefs/lfs.h"
int main(void)
{
 prepare_eeprom(); CHECK(i2c_eeprom_init()); hal.nvs.size = 4100;
 const struct lfs_config *config = eeprom_littlefs_hal();
 CHECK(config->block_size == 256 && config->block_count == (16384 - 4352) / 256);
 const uint8_t data[256] = {37};
 CHECK(config->prog(config, 0, 0, data, sizeof(data)) == 0);
 CHECK(memory[4351] == 255 && memory[4352] == 37 && memory[4608] == 255);
 CHECK(memory[4096] == 255); return 0;
}
