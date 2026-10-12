#include "support/control_host.h"
bool delay_sec(float seconds, delaymode_t mode) { host_delay_calls++; host_delay_seconds = seconds; host_delay_mode = mode; return true; }
