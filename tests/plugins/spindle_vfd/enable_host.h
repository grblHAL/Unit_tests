#pragma once
#include "vfd_host.h"
#include "ioports.h"

extern bool enable_levels[4];
extern unsigned enable_writes[4];
void enable_prepare_ports(bool conflict);
void enable_expect_claim(bool claimed);
