#pragma once
#include "support/engine_host.h"
#include "spindle_control.h"
#include "check.h"
static spindle_ptrs_t binding_driver;
static spindle_data_t native_feedback = {.rpm = 700}, external_feedback = {.rpm = 1200};
static unsigned native_reads, external_reads, native_resets, external_resets;
static spindle_data_t *native_encoder_read(spindle_data_request_t request)
{ CHECK(request == SpindleData_RPM); native_reads++; return &native_feedback; }
static spindle_data_t *external_encoder_read(spindle_data_request_t request)
{ CHECK(request == SpindleData_RPM); external_reads++; return &external_feedback; }
static void native_encoder_reset(void) { native_resets++; }
static void external_encoder_reset(void) { external_resets++; }
static void binding_spindle_write(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{ (void)spindle; (void)rpm; CHECK(!state.on); }
static spindle_state_t binding_spindle_read(spindle_ptrs_t *spindle)
{ (void)spindle; return (spindle_state_t){0}; }
static const spindle_data_ptrs_t binding_encoder = {.get=external_encoder_read,.reset=external_encoder_reset};
static inline void register_binding_spindle(bool variable)
{
    binding_driver = (spindle_ptrs_t){.type=SpindleType_Basic,.ref_id=7,
        .cap={.variable=variable},.set_state=binding_spindle_write,.get_state=binding_spindle_read,
        .get_data=native_encoder_read,.reset_data=native_encoder_reset};
    CHECK(spindle_register(&binding_driver,"encoder host") == 0);
}
static inline void prepare_encoder_binding(bool variable, bool activate)
{
    engine_prepare(); sys.cold_start = true; settings.spindle.encoder_spindle = 7;
    register_binding_spindle(variable); if(activate) CHECK(spindle_select(0));
}
