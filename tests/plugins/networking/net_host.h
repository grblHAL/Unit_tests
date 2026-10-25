#pragma once
#include "check.h"
#include "networking.h"
extern network_info_t net_infos[2];
extern bool net_available[2], net_file;
extern unsigned net_previous_reports, net_previous_streams, net_registrations;
extern char net_output[4096];
void net_prepare(void);
void net_add(unsigned index, network_status_t status);
void net_clear(void);
status_code_t net_command(void);
