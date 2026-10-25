# Tool-table scenarios awaiting source compatibility

These seven authored scenarios are unregistered and have NOT executed. They are
not part of current suite totals, CI choices, coverage or known-result counts.
The bounded file-backend fixture itself remains unvalidated at runtime.

Original Plugins_misc265711922037cab6b6e47a9560ef11da3a6e5f83 assigns
`writeTools(tool_data_t *)` to `grbl.tool_table.set_tool` at tooltable.c452.
Pinned CORE b01f481072edecac33d5e40c25869359a5b3fa1f requires
`bool (*)(tool_data_t *, bool persist)` (core_handlers.h151). Windows Clang23
rejects the assignment unchanged. Scenario callers use CORE's actual two-argument
contract. No cast, header bypass, source patch or older-CORE fallback is allowed.

The compiler also flags the uint_fast8_t parser index versus300-byte buffer bound.
Do not execute oversized/malformed lines to reproduce unsafe behavior. All proposed
file content is short, ordinary newline-terminated LinuxCNC-style records.

Scenarios cover mount/load through actual CORE VFS/numeric helpers, identity/
pocket/geometry/name handling, save/reload, clear/reload, absent/read/write-open
failure recovery and hook/report chains. The random-toolchanger sparse-pocket
scenario is only a candidate: source allocates by entry count then indexes by
pocket number, but no runtime outcome has been verified or classified.

Once unchanged upstream source is compatible, configure this folder separately,
validate fixtures and all scenarios, classify actual outcomes honestly, then move
supported cases into the maintained suite. Do not add to default builds early.
