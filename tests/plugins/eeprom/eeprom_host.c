#include "eeprom_host.h"
grbl_hal_t hal;
bool start_ok = true, probe_ok = true;
unsigned starts, probes, transfers, delays, fail_transfer;
uint8_t memory[131072];
struct transaction transactions[2048];
unsigned page_size(void)
{
#if EEPROM_ENABLE == 16
 return 16;
#elif EEPROM_ENABLE == 1024
 return 256;
#elif EEPROM_ENABLE >= 128
 return 64;
#else
 return 32;
#endif
}
i2c_cap_t i2c_start(void) { starts++; return (i2c_cap_t){.started = start_ok}; }
bool i2c_probe(i2c_address_t address) { CHECK(address == 0x50); probes++; return probe_ok; }
bool i2c_transfer(i2c_transfer_t *transfer, bool read)
{
 uint32_t address;
#if EEPROM_ENABLE == 16
 CHECK(transfer->word_addr_bytes == 1); CHECK(transfer->address >= 0x50 && transfer->address <= 0x57);
 address = ((transfer->address & 7) << 8) | transfer->word_addr;
#else
 CHECK(transfer->word_addr_bytes == 2); CHECK(transfer->address == 0x50 || (EEPROM_ENABLE == 1024 && transfer->address == 0x51));
 address = ((transfer->address & 1) << 16) | transfer->word_addr;
#endif
 CHECK(transfers < 2048); CHECK(address + transfer->count <= sizeof(memory));
 transactions[transfers++] = (struct transaction){address, transfer->count, read};
 if(fail_transfer && transfers == fail_transfer) return false;
 if(!read) CHECK((address % page_size()) + transfer->count <= page_size());
 if(read) memcpy(transfer->data, memory + address, transfer->count);
 else memcpy(memory + address, transfer->data, transfer->count);
 return true;
}
static void delay_ms(uint32_t ms, delay_callback_ptr callback) { CHECK(ms == 7 && callback == NULL); delays++; }
void prepare_eeprom(void) { memset(memory, 255, sizeof(memory)); hal.delay_ms = delay_ms; }
