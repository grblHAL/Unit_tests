# Pending core features

These are pending implementation, not confirmed defects. Tests record current
unsupported behavior without `known_bug` or expected-failure labels.

## Plain G71 and G72 lathe roughing

**Recorded:** 2026-10-12

**Status:** TODO - not fully added yet in the pinned core.

Plain G71/G72 roughing is pending upstream implementation. The current tests
verify that these commands reject the block without dispatching a roughing
plugin or changing position:

- [G71](cases/lathe_ngc/g71_pending_implementation_does_not_dispatch_roughing.c)
- [G72](cases/lathe_ngc/g72_pending_implementation_does_not_dispatch_roughing.c)

The current rejection is `Status_GcodeUnusedWords` in the pinned core. The
existing G70 and fractional G71.1/G71.2/G72.1/G72.2 tests exercise parser/plugin
interfaces using a capture handler; they do not implement roughing geometry.
The default [mc_lathe_cycle handler](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/motion_control.c#L806-L810)
also remains a placeholder.

When plain G71/G72 support is added, update these two tests to check successful
execution/dispatch and the required arguments, then delete this TODO entry.
