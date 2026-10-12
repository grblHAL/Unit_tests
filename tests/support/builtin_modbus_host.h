#pragma once
#include "support/builtin_macro_host.h"
#include "modbus.h"
static unsigned builtin_bus_calls;
static modbus_message_t builtin_bus_request;
static uint8_t builtin_reply_registers = 1;
static uint16_t builtin_reply_values[3] = {17, 34, 51};
static uint8_t builtin_bus_exception;
static bool builtin_bus_timeout, builtin_bus_failure;
static bool builtin_bus_up(void) { return true; }
static bool builtin_bus_send(modbus_message_t *message, const modbus_callbacks_t *callbacks, bool block)
{
    CHECK(block && callbacks != NULL);
    builtin_bus_calls++;
    builtin_bus_request = *message;
    if(builtin_bus_failure) return false;
    if(builtin_bus_timeout) callbacks->on_rx_timeout(ModBus_Timeout, NULL);
    else if(builtin_bus_exception) callbacks->on_rx_exception(builtin_bus_exception, NULL);
    else {
        modbus_message_t reply = {.rx_length = (uint8_t)(5 + 2 * builtin_reply_registers), .adu = {message->adu[0], message->adu[1], (uint8_t)(2 * builtin_reply_registers)}};
        if(message->adu[1] == ModBus_ReadExceptionStatus) {
            reply.rx_length = 5;
            reply.adu[2] = 0xA5;
        } else if(modbus_get_function_properties((modbus_function_t)message->adu[1])->is_write) {
            reply.rx_length = 8;
            memcpy(reply.adu, message->adu, 6);
        } else if(modbus_get_function_properties((modbus_function_t)message->adu[1])->packed) {
            uint16_t count = modbus_read_u16(&message->adu[4]);
            reply.adu[2] = (uint8_t)((count + 7) / 8);
            CHECK(reply.adu[2] <= 2);
            reply.rx_length = (uint8_t)(5 + reply.adu[2]);
            reply.adu[3] = 0xAA;
            reply.adu[4] = 0x01;
        } else for(unsigned i = 0; i < builtin_reply_registers; i++) modbus_write_u16(&reply.adu[3 + 2 * i], builtin_reply_values[i]);
        callbacks->on_rx_packet(&reply);
    }
    return true;
}
static inline void prepare_builtin_modbus(void)
{
    prepare_settings_store();
    static const modbus_api_t api = {.interface = Modbus_InterfaceRTU, .is_up = builtin_bus_up, .send = builtin_bus_send};
    CHECK(modbus_register_api(&api));
    CHECK(modbus_isup().rtu);
}
