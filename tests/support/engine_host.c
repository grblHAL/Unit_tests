#include "support/engine_host.h"
#include "state_machine.h"
#include "crc.h"
#include "check.h"
#include <string.h>

uint32_t engine_ticks;
unsigned engine_irq_depth;
char engine_output[4096];
static uint8_t storage[8192];
static tool_data_t tool;
static tool_table_entry_t entry = {.data = &tool};

static void irq_disable(void) { engine_irq_depth++; }
static void irq_enable(void) { CHECK(engine_irq_depth > 0); engine_irq_depth--; }
static uint32_t ticks(void) { return engine_ticks; }
static void delay(uint32_t ms, delay_callback_ptr callback) { engine_ticks += ms; if(callback) callback(); }
static void set_bits(volatile uint_fast16_t *value, uint_fast16_t bits) { *value |= bits; }
static uint_fast16_t clear_bits(volatile uint_fast16_t *value, uint_fast16_t bits) { uint_fast16_t before = *value; *value &= ~bits; return before; }
static uint_fast16_t set_value(volatile uint_fast16_t *value, uint_fast16_t bits) { uint_fast16_t before = *value; *value = bits; return before; }
static void write_output(const char *text) { CHECK(strlen(engine_output) + strlen(text) < sizeof(engine_output)); strcat(engine_output, text); }
static tool_table_entry_t *get_tool(tool_id_t id) { CHECK(id == 0); return &entry; }
static status_code_t report_status(status_code_t code) { CHECK(code == Status_OK); return code; }
static uint8_t get_byte(uint32_t address) { CHECK(address < sizeof(storage)); return storage[address]; }
static void put_byte(uint32_t address, uint8_t value) { CHECK(address < sizeof(storage)); storage[address] = value; }
static bool read_nvs(uint8_t *dest, uint32_t source, uint32_t size, bool checksum)
{
    CHECK(source + size + NVS_CRC_BYTES <= sizeof(storage));
    memcpy(dest, storage + source, size);
    uint16_t crc = checksum ? calc_checksum(dest, size) : 0;
    return !checksum || (storage[source + size] == (uint8_t)crc
#if NVS_CRC_BYTES > 1
        && storage[source + size + 1] == (uint8_t)(crc >> 8)
#endif
    );
}
static bool write_nvs(uint32_t dest, uint8_t *source, uint32_t size, bool checksum)
{
    CHECK(dest + size + NVS_CRC_BYTES <= sizeof(storage));
    memcpy(storage + dest, source, size);
    if(checksum) {
        uint16_t crc = calc_checksum(source, size);
        storage[dest + size] = (uint8_t)crc;
#if NVS_CRC_BYTES > 1
        storage[dest + size + 1] = (uint8_t)(crc >> 8);
#endif
    }
    return true;
}
void engine_prepare(void)
{
    memset(&hal, 0, sizeof(hal)); memset(&sys, 0, sizeof(sys));
    memset(&grbl, 0, sizeof(grbl)); memset(&settings, 0, sizeof(settings));
    hal.irq_disable = irq_disable; hal.irq_enable = irq_enable;
    hal.set_bits_atomic = set_bits; hal.clear_bits_atomic = clear_bits; hal.set_value_atomic = set_value;
    hal.get_elapsed_ticks = ticks; hal.delay_ms = delay;
    hal.stream.write = hal.stream.write_all = write_output;
    hal.nvs.type = NVS_Emulated; hal.nvs.get_byte = get_byte; hal.nvs.put_byte = put_byte;
    hal.nvs.memcpy_from_nvs = read_nvs; hal.nvs.memcpy_to_nvs = write_nvs;
    grbl.tool_table.get_tool = get_tool; grbl.report.status_message = report_status;
    sys.override.feed_rate = sys.override.rapid_rate = 100;
    settings.planner_buffer_blocks = 16; settings.junction_deviation = .01f;
    settings.flags.g92_is_volatile = true;
    for(unsigned i = 0; i < N_AXIS; i++) {
        settings.axis[i].steps_per_mm = 80; settings.axis[i].max_rate = 1000;
        settings.axis[i].acceleration = 100; settings.axis[i].max_travel = -200;
    }
}
void engine_parser_prepare(void)
{
    engine_prepare(); sys.cold_start = true;
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    CHECK(spindle_select(0)); gc_init(false); CHECK(plan_reset()); limits_init();
    state_set(STATE_CHECK_MODE);
}
bool driver_init(void)
{
    CHECK(false);
    return false;
}
