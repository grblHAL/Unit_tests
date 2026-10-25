# Source contract and scope

Seven independent M-code/binding/provider scenarios execute original select.c
and real CORE spindle registration with original EEPROM/CRC settings. No runtime
defect allowance; original sources remain Plugins_spindle8a3ae47f and
COREb01f4810, unchanged. N_SPINDLE2/N_SYS_SPINDLE1 only.

Tool-threshold setter is incompatible with registered public setting function
type: select.c set_tool_start takes uint32_t while Format_Int16 dispatch via
setting_set_int_ptr takes uint_fast16_t (settings.h1098/settings.c3648). Initial
ordinary CTest11/11 concealed three recovering UBSan errors; strict reporting
correctly rejects them. Four dependent tool/persistence files are unregistered
proposals. Do not hide the signature mismatch or claim process restart verified.
No unsafe reproduction is needed on unchanged pins.

Active cases cover consumed-word M-code handoff, selection, invalid values,
bindings, prior callbacks, reports and setup/storage failure. Actual parser
motion, physical spindle switching, tool thresholds, process restart, larger
spindle counts and simultaneous system variants remain unfinished.
