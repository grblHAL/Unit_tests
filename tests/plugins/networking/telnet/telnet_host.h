#pragma once
#include "driver.h"
#include "check.h"
#include "networking.h"
#include "grbl/task.h"
void telnet_prepare(void);
void telnet_connect(void);
void telnet_receive(const char *first, const char *second);
void telnet_finish(void);
extern struct tcp_pcb telnet_client;
extern unsigned tcp_acks, tcp_frees, tcp_outputs, tcp_closes, tcp_aborts, network_events;
extern unsigned rt_calls, block_calls;
extern bool tcp_bind_ok;
extern uint8_t tcp_bytes[2048];
extern size_t tcp_length;
extern err_t tcp_write_result;
extern tcp_accept_fn listener_accept;
extern void *listener_arg;
