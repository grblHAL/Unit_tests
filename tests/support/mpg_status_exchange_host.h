#pragma once
#include "support/mpg_independent_report_host.h"
#include "system.h"
typedef enum { ExchangeWCS, ExchangeInches, ExchangeFlood, ExchangeMist, ExchangeCoolantOff, ExchangeWCSReset } status_exchange_t;
static coolant_state_t exchange_coolant;
static unsigned exchange_coolant_calls;
static coolant_state_t exchange_get_coolant(void) { return exchange_coolant; }
static void exchange_set_coolant(coolant_state_t state) { exchange_coolant = state; exchange_coolant_calls++; }
static control_signals_t exchange_controls(void) { return (control_signals_t){0}; }
static inline void exchange_block(const char *text)
{
    char block[96];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    CHECK(gc_execute_block(block) == Status_OK);
}
static inline bool exchange_has_field(const char *output, const char *field)
{
    const char *match = strstr(output, field);
    return match && (match[strlen(field)] == '|' || match[strlen(field)] == '>');
}
static inline void check_status_exchange(status_exchange_t change, bool primary_first)
{
    prepare_mpg_stream();
    settings.status_report.overrides = false;
    settings.status_report.work_coord_offset = true;
    hal.coolant_cap.mist = true;
    hal.coolant.get_state = exchange_get_coolant;
    hal.coolant.set_state = exchange_set_coolant;
    hal.control.get_state = exchange_controls;
    grbl.on_execute_realtime = protocol_execute_noop;
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    if(change == ExchangeCoolantOff) exchange_block("M8");
    if(change == ExchangeWCSReset) exchange_block("G55");
    request_primary_status(); request_pendant_status();
    primary_output[0] = pendant_output[0] = '\0';
    const char *expected = NULL;
    switch(change) {
        case ExchangeWCS:
            exchange_block("G55");
            CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G55);
            expected = "|WCS:G55";
            break;
        case ExchangeInches: {
            char setting[] = "$13=1";
            CHECK(system_execute_line(setting, hal.stream.write) == Status_OK);
            exchange_block("G10L2P1X25.4");
            CHECK(settings.flags.report_inches);
            expected = "|WCO:1.0000,0.0000,0.0000";
            break;
        }
        case ExchangeWCSReset:
            exchange_block("G54");
            CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
            expected = "|WCS:G54";
            break;
        case ExchangeCoolantOff:
            exchange_block("M9");
            CHECK(exchange_coolant.value == 0 && exchange_coolant_calls == 2);
            expected = "|A:";
            break;
        case ExchangeFlood:
            exchange_block("M8");
            CHECK(exchange_coolant.flood && !exchange_coolant.mist && exchange_coolant_calls == 1);
            expected = "|A:F";
            break;
        case ExchangeMist:
            exchange_block("M7");
            CHECK(exchange_coolant.mist && !exchange_coolant.flood && exchange_coolant_calls == 1);
            expected = "|A:M";
            break;
    }
    CHECK(expected != NULL);
    primary_output[0] = pendant_output[0] = '\0';
    if(primary_first) {
        request_primary_status();
        CHECK(exchange_has_field(primary_output, expected) && exchange_has_field(pendant_output, expected));
        primary_output[0] = pendant_output[0] = '\0';
        request_pendant_status();
        CHECK(exchange_has_field(pendant_output, expected) && primary_output[0] == '\0');
    } else {
        request_pendant_status();
        CHECK(exchange_has_field(pendant_output, expected) && primary_output[0] == '\0');
        primary_output[0] = pendant_output[0] = '\0';
        request_primary_status();
        CHECK(exchange_has_field(primary_output, expected) && exchange_has_field(pendant_output, expected));
    }
    CHECK(state_get() == STATE_IDLE && !sys.mpg_mode && hal.stream.read == primary_input);
}
