#include "hal.h"
#include "protocol.h"
#include "state_machine.h"
grbl_hal_t hal;
bool protocol_execute_realtime(void) { return true; }
bool protocol_exec_rt_system(void) { return true; }
bool state_door_reopened(void) { return false; }
