#include "support/report_host.h"
static tool_data_t tools[] = {
    {.tool_id = 1, .offset.values = {1, 2, 3}},
    {.tool_id = 2, .offset.values = {4, 5, 6}},
    {.tool_id = 0},
    {.tool_id = -1}
};
static tool_table_entry_t entries[] = {
    {.name = "End mill", .data = &tools[0], .pocket = 7},
    {.name = "Drill", .data = &tools[1], .pocket = -1},
    {.data = &tools[2], .pocket = 3},
    {.data = &tools[3], .pocket = 4}
};
static unsigned paced_rows;
static tool_table_entry_t *indexed_tool(uint32_t index)
{
    CHECK(index >= 1 && index <= 4);
    return &entries[index - 1];
}
static void pace_named_row(uint32_t milliseconds, void (*callback)(void))
{
    CHECK(milliseconds == 5 && callback == NULL && paced_rows < 2);
    CHECK(strstr(engine_output, paced_rows ? "Drill]" ASCII_EOL : "End mill|7]" ASCII_EOL));
    paced_rows++;
}
int main(void)
{
    prepare_report();
    grbl.tool_table.n_tools = 4;
    grbl.tool_table.get_tool_by_idx = indexed_tool;
    hal.delay_ms = pace_named_row;
    report_ngc_parameters();
    CHECK(paced_rows == 2);
    CHECK(strstr(engine_output, "[T:1|1.000,2.000,3.000|0.000|6,0,0|End mill|7]" ASCII_EOL));
    CHECK(strstr(engine_output, "[T:2|4.000,5.000,6.000|0.000|6,0,0|Drill]" ASCII_EOL));
    CHECK(strstr(engine_output, "[T:0|") == NULL);
    CHECK(strstr(engine_output, "|4]" ASCII_EOL) == NULL);
    settings.macro_atc_flags.random_toolchanger = true;
    paced_rows = 0;
    engine_output[0] = '\0';
    report_ngc_parameters();
    CHECK(paced_rows == 2);
    CHECK(strstr(engine_output, "[T:0|0.000,0.000,0.000|0.000|6,0,0||3]" ASCII_EOL));
    CHECK(strstr(engine_output, "[T:1|1.000,2.000,3.000|0.000|6,0,0|End mill|7]" ASCII_EOL));
    CHECK(strstr(engine_output, "[T:2|4.000,5.000,6.000|0.000|6,0,0|Drill]" ASCII_EOL));
    CHECK(strstr(engine_output, "|4]" ASCII_EOL) == NULL);
    return EXIT_SUCCESS;
}
