# Spindle tool-threshold and persistence proposals

Four files are unregistered after strict reporting caught undefined calls in
three writer scenarios. Original select.c set_tool_start takes uint32_t while
registered Format_Int16 setting dispatch uses CORE setting_set_int_ptr with
uint_fast16_t. CORE settings.c3648 uses that same public function type. On this
Windows Clang target uint_fast16_t is unsigned short; original setter is not
compatible. The reader depends on the writer and is also unregistered.

Do not cast to a hand-picked source-specific type to hide the registered ABI
mismatch, modify original source or reexecute unsafe calls on unchanged pins.
These assertions remain proposals and have no passing strict/persistence claim.
Initial ordinary11-case CTest was green but strict classification found3 failed
sanitizer results,8 clean; that is not validated tool/persistence support.
Original plugin8a3ae47f/COREb01f4810. Review upstream compatibility before
registering these files. Seven independent M-code/binding/provider cases remain
active with an empty diagnostics allowance list.
