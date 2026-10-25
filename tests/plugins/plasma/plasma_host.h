#pragma once
#include "eeprom_host.h"
#include "grbl/fs_embedded.h"
#include "grbl/nvs_buffer.h"
#include "grbl/task.h"
#include "thc.h"
extern setting_details_t *plasma_details;
extern unsigned plasma_warnings, plasma_prior_comments, plasma_prior_reports, plasma_steps;
extern char plasma_output[8192];
extern bool plasma_storage_ok;
void plasma_init(void);
void plasma_prepare(unsigned inputs, bool output_step);
void plasma_load(void);
status_code_t plasma_list(void);
status_code_t plasma_comment(char *comment);
material_t plasma_material(int id);
void plasma_mount(const embedded_file_t **files);

extern uint64_t plasma_micros;
extern float plasma_inputs[3];
extern unsigned plasma_up_steps, plasma_down_steps, plasma_waits, plasma_torch_starts,
    plasma_torch_stops, plasma_holds, plasma_resets, plasma_claims, plasma_releases;
extern bool plasma_torch_on, plasma_motor_claimed, plasma_wait_ok;
extern unsigned plasma_fail_waits;
extern sys_state_t plasma_state;
extern spindle_ptrs_t *plasma_motor;
void plasma_runtime_prepare(void);
int32_t plasma_wait_input(uint8_t port, wait_mode_t mode, float timeout);
void plasma_input(const char *description, bool on);
void plasma_set(setting_id_t id, float value);
void plasma_boot(void);
void plasma_tick(unsigned ms);
void plasma_feed(float programmed, float actual);

extern float plasma_voltage;
void plasma_set_port(setting_id_t id, float value);
