#pragma once
#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"
typedef enum { BusReply, BusTimeout, BusException, BusReject } bus_result_t;
static bus_result_t bus_result;
static unsigned bus_requests, bus_callbacks;
static modbus_message_t bus_request;
static modbus_response_t bus_response;
static uint16_t bus_read_values[MODBUS_MAX_REGISTERS] = {0x1234, 0x5678, 0x9ABC, 0xDEF0};
static inline void bus_completed(modbus_response_t *response)
{
    bus_callbacks++;
    bus_response = *response;
}
static bool bus_send_transaction(modbus_message_t *message, const modbus_callbacks_t *callbacks, bool block)
{
    CHECK(block && callbacks != NULL && message->crc_check);
    CHECK(message->tx_length <= MODBUS_MAX_ADU_SIZE && message->rx_length <= MODBUS_MAX_ADU_SIZE);
    bus_requests++;
    bus_request = *message;
    if(bus_result == BusReject) return false;
    if(bus_result == BusTimeout) callbacks->on_rx_timeout(ModBus_Timeout, message->context);
    else if(bus_result == BusException) callbacks->on_rx_exception(ModBus_IllegalDataAddress, message->context);
    else {
        modbus_message_t reply = {.adu = {message->adu[0], message->adu[1]}};
        const modbus_function_properties_t *properties = modbus_get_function_properties((modbus_function_t)message->adu[1]);
        CHECK(properties != NULL);
        if(properties->is_write) {
            memcpy(reply.adu, message->adu, 6);
            reply.rx_length = 8;
        } else {
            CHECK(!properties->packed);
            uint16_t count = modbus_read_u16(&message->adu[4]);
            CHECK(count <= MODBUS_MAX_REGISTERS);
            reply.adu[2] = (uint8_t)(count * 2);
            reply.rx_length = (uint8_t)(count * 2 + 5);
            for(unsigned i = 0; i < count; i++) modbus_write_u16(&reply.adu[3 + 2 * i], bus_read_values[i]);
        }
        callbacks->on_rx_packet(&reply);
    }
    return true;
}
static inline void prepare_bus_transactions(void)
{
    const modbus_api_t api = {.interface = Modbus_InterfaceRTU, .send = bus_send_transaction};
    CHECK(modbus_register_api(&api));
}
