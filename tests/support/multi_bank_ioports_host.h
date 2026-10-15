#pragma once
#include "support/ioports_host.h"
static xbar_t bank_digital_pins[3][2][2], bank_analog_pins[2][2][2];
static io_ports_data_t bank_digital_data[3], bank_analog_data[2];
static unsigned bank_output_calls, bank_input_calls, bank_irq_calls, bank_event_calls;
static uint8_t last_bank, last_local_port, bank_irq_user_port;
static io_port_type_t last_bank_type;
static float bank_output_value, bank_wait_timeout;
static wait_mode_t bank_wait_mode;
static pin_irq_mode_t bank_irq_mode;
static ioport_interrupt_callback_ptr bank_irq_callback;
static bool bank_analog_output_ok = true;
static uint8_t event_port[16];
static io_port_type_t event_type[16];
static float event_value[16];
static void bank_event(uint8_t port, io_port_type_t type, float value)
{
    CHECK(bank_event_calls < 16);
    event_port[bank_event_calls] = port; event_type[bank_event_calls] = type;
    event_value[bank_event_calls++] = value;
}
#define DIGITAL_BANK(B) \
static xbar_t *digital_info_##B(io_port_direction_t d, uint8_t p) { return p < bank_digital_data[B].cfg[d].n_ports ? &bank_digital_pins[B][d][p] : NULL; } \
static void digital_descr_##B(io_port_direction_t d, uint8_t p, const char *s) { CHECK(p < bank_digital_data[B].cfg[d].n_ports); bank_digital_pins[B][d][p].description = s; } \
static void digital_out_##B(uint8_t p, bool value) { CHECK(p < bank_digital_data[B].out.n_ports); last_bank = B; last_local_port = p; last_bank_type = Port_Digital; bank_output_value = value; bank_output_calls++; } \
static int32_t digital_wait_##B(uint8_t p, wait_mode_t m, float t) { CHECK(p < bank_digital_data[B].in.n_ports); last_bank = B; last_local_port = p; bank_wait_mode = m; bank_wait_timeout = t; bank_input_calls++; return (B + 1) * 10 + p; } \
static bool digital_irq_##B(uint8_t p, uint8_t u, pin_irq_mode_t m, ioport_interrupt_callback_ptr cb) { CHECK(p < bank_digital_data[B].in.n_ports); last_bank = B; last_local_port = p; bank_irq_user_port = u; bank_irq_mode = m; bank_irq_callback = cb; bank_irq_calls++; return true; }
DIGITAL_BANK(1)
DIGITAL_BANK(2)
#undef DIGITAL_BANK
#define ANALOG_BANK(B) \
static xbar_t *analog_info_##B(io_port_direction_t d, uint8_t p) { return p < bank_analog_data[B].cfg[d].n_ports ? &bank_analog_pins[B][d][p] : NULL; } \
static void analog_descr_##B(io_port_direction_t d, uint8_t p, const char *s) { CHECK(p < bank_analog_data[B].cfg[d].n_ports); bank_analog_pins[B][d][p].description = s; } \
static bool analog_out_##B(uint8_t p, float value) { CHECK(p < bank_analog_data[B].out.n_ports); last_bank = B; last_local_port = p; last_bank_type = Port_Analog; bank_output_value = value; bank_output_calls++; return bank_analog_output_ok; } \
static int32_t analog_wait_##B(uint8_t p, wait_mode_t m, float t) { CHECK(p < bank_analog_data[B].in.n_ports); last_bank = B; last_local_port = p; bank_wait_mode = m; bank_wait_timeout = t; bank_input_calls++; return (B + 1) * 100 + p; }
ANALOG_BANK(0)
ANALOG_BANK(1)
#undef ANALOG_BANK
static inline void prepare_multi_bank_ioports_counts(uint8_t first_in, uint8_t first_out, uint8_t second_in, uint8_t second_out)
{
    prepare_ioports();
    for(unsigned bank = 1; bank < 3; bank++) {
        unsigned count = bank == 1 ? 2 : 1;
        bank_digital_data[bank] = (io_ports_data_t){.external = true, .in.n_ports = count, .out.n_ports = count};
        for(unsigned d = 0; d < 2; d++) for(unsigned p = 0; p < count; p++) {
            xbar_t *pin = &bank_digital_pins[bank][d][p];
            pin->id = p;
            pin->function = (pin_function_t)((d == Port_Input ? Input_Aux0 : Output_Aux0) + bank * 2 + p);
            pin->cap.input = pin->mode.input = d == Port_Input;
            pin->cap.output = pin->mode.output = d == Port_Output;
        }
    }
    io_digital_t digital[] = {
        {.ports = &bank_digital_data[1], .get_pin_info = digital_info_1, .set_pin_description = digital_descr_1,
         .digital_out = digital_out_1, .wait_on_input = digital_wait_1, .register_interrupt_handler = digital_irq_1},
        {.ports = &bank_digital_data[2], .get_pin_info = digital_info_2, .set_pin_description = digital_descr_2,
         .digital_out = digital_out_2, .wait_on_input = digital_wait_2, .register_interrupt_handler = digital_irq_2}
    };
    CHECK(ioports_add_digital(&digital[0]) && ioports_add_digital(&digital[1]));
    for(unsigned bank = 0; bank < 2; bank++) {
        CHECK(first_in <= 2 && first_out <= 2 && second_in <= 2 && second_out <= 2);
        bank_analog_data[bank] = (io_ports_data_t){.external = true,
            .in.n_ports = bank ? second_in : first_in,
            .out.n_ports = bank ? second_out : first_out};
        for(unsigned d = 0; d < 2; d++) for(unsigned p = 0; p < 2; p++) {
            xbar_t *pin = &bank_analog_pins[bank][d][p];
            pin->id = p;
            pin->function = (pin_function_t)((d == Port_Input ? Input_Analog_Aux0 : Output_Analog_Aux0) + bank * 2 + p);
            pin->cap.analog = pin->mode.analog = true;
            pin->cap.input = pin->mode.input = d == Port_Input;
            pin->cap.output = pin->mode.output = d == Port_Output;
        }
    }
    io_analog_t analog[] = {
        {.ports = &bank_analog_data[0], .get_pin_info = analog_info_0, .set_pin_description = analog_descr_0,
         .analog_out = analog_out_0, .wait_on_input = analog_wait_0},
        {.ports = &bank_analog_data[1], .get_pin_info = analog_info_1, .set_pin_description = analog_descr_1,
         .analog_out = analog_out_1, .wait_on_input = analog_wait_1}
    };
    CHECK(ioports_add_analog(&analog[0]) && ioports_add_analog(&analog[1]));
    grbl.on_port_out = bank_event;
}

static inline void prepare_multi_bank_ioports(void)
{
    prepare_multi_bank_ioports_counts(2, 2, 2, 2);
}

static unsigned bank_received_irq_calls;
static uint8_t bank_received_irq_port;
static bool bank_received_irq_state;
static inline void bank_consumer_irq(uint8_t port, bool high)
{
    bank_received_irq_calls++; bank_received_irq_port = port; bank_received_irq_state = high;
}
