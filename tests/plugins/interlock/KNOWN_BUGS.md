# Scope and remaining work

Nineteen original-source cases with real CORE declarations and simulated public settings-registration, port metadata/value, NVS and alarm/reset boundaries. Tests observe requested E-stop/alarm and suppressed hardware callback; they do not establish physical emergency-stop timing or full controller shutdown. Valid registered setting callbacks configure slots; private state is untouched. Default four forward/four inverse slots plus source-supported1/2 and2/1
forward/inverse slot builds. Registered getters/save/load/restore, inverse-slot
disable and direction/polarity decisions have dedicated cases. These provider
callback tests do not establish protocol permission for settings writes in motion. Unreadable ports deliberately follow documented fail-open behavior; no endorsement of that policy. Clang23 warns about original uninitialized io_port_cfg_t const fields before ioports_cfg populates them; that one original-source warning stays visible and nonfatal, fixture warnings remain errors. No known runtime exception. Full settings parser/ISR/task ordering and multi-spindle support remain untested.
