#pragma once
#include "check.h"
#include "driver.h"
#include "fs_stream.h"
#include "grbl/fs_embedded.h"
#include "grbl/state_machine.h"
#include "grbl/stream_file.h"
#include "grbl/task.h"
void fs_stream_init(void);
bool fs_busy(void);
extern sys_state_t sd_state;
extern unsigned sd_resets, sd_flushes, sd_changes, sd_statuses, sd_completions, sd_acks,
    sd_realtime, sd_feedback;
extern char sd_output[8192];
extern enqueue_realtime_command_ptr sd_rt_handler;
void sd_prepare(bool mount);
void sd_mount(void);
void sd_clear_output(void);
void sd_run_tasks(void);
void sd_read(char *buffer, size_t size);
status_code_t sd_command(const char *command, char *args);
int32_t sd_serial_read(void);
