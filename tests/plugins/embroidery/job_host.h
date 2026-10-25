#pragma once
#include "driver.h"
#include "embroidery.h"
#include "../eeprom/eeprom_host.h"
#include "grbl/fs_embedded.h"
#include "grbl/motion_control.h"
#include "grbl/task.h"
#include "grbl/nvs_buffer.h"
extern setting_details_t *job_settings;
extern bool job_storage;
extern unsigned job_warnings, job_resets;
extern char job_output[4096];
void job_prepare(void);
vfs_file_t *job_dst(const uint8_t *stitches, size_t length);
vfs_file_t *job_pes(const uint8_t *stitches, size_t length);
void embroidery_init(void);

typedef struct
{
    coord_data_t target;
    float feed;
    bool rapid;
} job_motion_t;
extern job_motion_t job_motions[64];
extern unsigned job_motion_count, job_cancels, job_completions, job_feedback;
extern bool job_spindle_on;
extern uint_fast16_t job_planner_free;
void job_sync(bool enabled);
void job_needle(void);
int32_t job_serial_read(void);

extern unsigned job_syncs, job_holds;
void job_run_tasks(void);

extern bool job_mist_on;
extern unsigned job_mist_writes;

extern bool job_break_sensor;
void job_break(void);
void job_delay(uint16_t milliseconds);
void job_advance(uint32_t milliseconds);
