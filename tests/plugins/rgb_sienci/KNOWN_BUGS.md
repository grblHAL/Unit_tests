# Known regression - 2026-10-24

Sienci source df3409058f8bb9c202f560e562bb2671a0829561, default SLB32_DEV.
m2_stale_tool_color: a tool-selected color deferred while Modbus is busy can
execute after tool-change completion. Legacy rgb.c writes stale magenta over the
current idle white. Correct idle-color assertion remains; advanced rgbv2.c has a
toolchange_pending guard and passes the same supported callback sequence. Upstream
repair should re-evaluate live tool-change/state ownership before deferred color
writes. Remove only this exact WILL_FAIL/known_bug label once repaired. No
sanitizer diagnostic allowance.

# Scope

Thirty-one cases compile both original guarded source files in STATUS_LIGHT_ENABLE
2/3 configurations with real CORE types and nuts_bolts helpers. A bounded host task
queue delivers requested work at explicit simulated due times; it does not execute
CORE's scheduler or prove hardware latency. RGB HAL callbacks capture per-device
colors/intensity, two legacy strings and the advanced12-LED ring/offboard split.
Scenarios cover state palette, all animation families, busy retry, override and
parameter validation, program-completion sequence and hook chaining. Optional
previous state/tool/completion/M-code hooks and RGB write/intensity callbacks are
absent in dedicated cases. Offboard green/off/automatic persists across states;
active animation updates it on the next frame. E-stop ring pulses stop under
manual override and resume when automatic operation is restored. No private
plugin state or source is changed. Full parser/controller jobs, real task scheduling,
physical LEDs/DMA and remaining optional RGB/DEBUG configurations remain untested.
