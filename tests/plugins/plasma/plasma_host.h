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
