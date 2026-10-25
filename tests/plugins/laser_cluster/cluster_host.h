#pragma once
#include "check.h"
#include "driver.h"
extern bool cluster_file;
extern unsigned cluster_statuses, cluster_previous_streams, cluster_previous_resets,
    cluster_previous_reports, cluster_handler_inits;
extern status_code_t cluster_last_status;
extern char cluster_output[1024];
void lb_clusters_init(void);
void cluster_prepare(bool file, const char *data);
void cluster_source(const char *data);
void cluster_change(bool file, const char *data);
void cluster_drain(char *out, size_t size);
