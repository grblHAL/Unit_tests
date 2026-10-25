# Known defects and scope

Nine selected host scenarios pass with no known runtime exceptions. Original
Plugins_spindle8a3ae47f5a218834da9c742424c3dd22c5629fdb and
COREb01f481072edecac33d5e40c25869359a5b3fa1f remain unchanged.

Actual CORE registers three driver-supplied basic spindles, one laser-capable in
laser mode. Original offset.c hooks/settings use original EEPROM/CRC storage.
Host motion boundary captures rapid targets and models accepted completion by
updating step position at80 steps/mm. It returns documented Status_Handled on
success and Status_Aborted on abort; mc_line is not an ordinary Status_OK API.
Planner initialization/synchronization and coordinate conversion are boundary
models, not actual planner, step generation, machine hardware or native parser.
Do not infer full motion or electrical laser safety from these unit tests.

Offset-return requests, G92 adjustments, no movement at startup/zero offset,
nonlaser selection, abort-without-G92, in-process save/load and reporting hooks
execute. Abort-followed-by-new-selection policy and repeated same-laser select
semantics remain source-contract questions. No manufactured private plugin state,
new sanitizer allowance, source changes or assertion weakening.
