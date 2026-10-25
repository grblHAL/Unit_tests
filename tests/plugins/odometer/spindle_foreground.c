#include "odometer_host.h"
int main(void)
{
 odometer_prepare(); odometer_init(); spindle_ptrs_t spindle = {.id = 0, .set_state = odometer_driver_spindle};
 grbl.on_spindle_selected(&spindle); spindle.set_state(&spindle, (spindle_state_t){.on = On}, 500);
 odometer_ticks += 60000; unsigned before = transfers; spindle.set_state(&spindle, (spindle_state_t){0}, 0);
 CHECK(odometer_spindle_calls == 2 && odometer_selected_calls == 1 && odometer_task_count == 1 && transfers == before);
 odometer_run_tasks(); CHECK(transfers > before); CHECK(odometer_query(NULL) == Status_OK && strstr(odometer_output, "SPINDLEHRS 0:01"));
 spindle_ptrs_t second = {.id = 1, .set_state = odometer_driver_spindle}; grbl.on_spindle_selected(&second);
 CHECK(second.set_state == odometer_driver_spindle && odometer_selected_calls == 2); return 0;
}
