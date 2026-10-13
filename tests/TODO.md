# Pending core features

These are pending implementation, not confirmed defects. Tests record current
parser/plugin behavior without `known_bug` or expected-failure labels.

## Plain G71 and G72 lathe roughing

**Recorded:** 2026-10-12

**Status:** TODO - roughing geometry is pending; core parser dispatch is tested.

Terje's core `e65020a8389b19d3c03277e02f34219e25800e6a` now dispatches plain
G71/G72 to the roughing plugin interface with the correct motion code and
arguments. Tests capture that interface; they do not implement roughing geometry:

- [G71](cases/lathe_ngc/g71_passes_default_roughing_arguments_to_plugin.c)
- [G72](cases/lathe_ngc/g72_passes_default_roughing_arguments_to_plugin.c)

The existing G70 and fractional G71.1/G71.2/G72.1/G72.2 tests likewise exercise
parser/plugin interfaces using a capture handler.
The default [mc_lathe_cycle handler](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/motion_control.c#L806-L810)
also remains a placeholder.

When roughing geometry is implemented, add execution and endpoint tests against
that implementation, retain the parser/interface tests, and delete this TODO entry.
