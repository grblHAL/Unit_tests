#pragma once
#include "support/human_metadata_report_host.h"
static unsigned name_chunk_calls;
static void name_write_bytes(const uint8_t *data, uint16_t length)
{
    CHECK(length > 0);
    size_t position = strlen(engine_output);
    CHECK(position + length < sizeof(engine_output));
    memcpy(engine_output + position, data, length); engine_output[position + length] = '\0';
    name_chunk_calls++;
}
static setting_id_t normalize_name_channel(setting_id_t id)
{ return id >= 1001 && id <= 1005 && (id - 1001) % 2 == 0 ? (setting_id_t)1001 : 0; }
static inline void prepare_numbered_setting_name(const char *name, bool subgroups)
{
    human_metadata_setting.name = name;
    human_metadata_setting.flags.increment = 2;
    human_metadata_setting.flags.subgroups = subgroups;
    human_metadata_details.normalize = normalize_name_channel;
    prepare_human_metadata(); hal.stream.write_n = name_write_bytes;
}
