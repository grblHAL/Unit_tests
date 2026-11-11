#include "enable_host.h"

bool enable_levels[4];
unsigned enable_writes[4];
static xbar_t pins[4];

static xbar_t *pin_info(io_port_direction_t direction, uint8_t port)
{
    return direction == Port_Output && port < 4 ? &pins[port] : NULL;
}
static void describe(io_port_direction_t direction, uint8_t port, const char *text)
{
    CHECK(direction == Port_Output && port < 4 && text);
    pins[port].description = text;
}
static void digital(uint8_t port, bool on)
{
    CHECK(port < 4);
    enable_levels[port] = on;
    enable_writes[port]++;
}
void enable_prepare_ports(bool conflict)
{
    for(unsigned port = 0; port < 4; port++)
        pins[port] = (xbar_t){.id = port, .function = Output_Aux0 + port, .cap.output = On};
    static io_ports_data_t data;
    static io_digital_t io;
    data.out.n_ports = 4;
    io = (io_digital_t){.ports = &data, .get_pin_info = pin_info,
        .set_pin_description = describe, .digital_out = digital};
    CHECK(ioports_add_digital(&io));
    /* Move free-port indices before VFD initialization: configuration uses aux 3. */
    uint8_t port = conflict ? 3 : 1;
    CHECK(ioport_claim(Port_Digital, Port_Output, &port, "Other plugin"));
}
void enable_expect_claim(bool claimed)
{
    CHECK(pins[3].description != NULL);
    CHECK((strcmp(pins[3].description, "VFD spindle enable") == 0) == claimed);
    CHECK(!enable_writes[0] && !enable_writes[1] && !enable_writes[2]);
}
void setting_remove_elements(setting_id_t id, uint32_t mask, bool trim)
{
    (void)id; (void)mask; (void)trim;
}
void settings_write_global(void) { CHECK(false); }

#if N_SPINDLE > 1 && N_SYS_SPINDLE == 1
/* The host selects the first VFD directly rather than loading the select plugin. */
int8_t spindle_select_get_binding(spindle_id_t id) { return id == 0 ? 0 : -1; }
#endif
