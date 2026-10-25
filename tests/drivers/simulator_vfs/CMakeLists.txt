cmake_minimum_required(VERSION 3.20)
project(grblhal_simulator_vfs_tests LANGUAGES C)
include(../../components.cmake)
foreach(behavior file_io directories listing nested_listing missing_paths remount_missing submount unsupported_ops pending_truncate)
  component_case(driver_simulator_vfs.${behavior} vfs_${behavior}.c vfs_host.c
    "${HARNESS_ROOT}/drivers/simulator/src/fs_posix.c" "${COMPONENT_CORE_ROOT}/vfs.c"
    "${COMPONENT_CORE_ROOT}/strutils.c" "${COMPONENT_CORE_ROOT}/nuts_bolts.c"
    "${HARNESS_ROOT}/tests/plugins/misc/misc_host.c")
  target_include_directories(driver_simulator_vfs.${behavior} PRIVATE "${HARNESS_ROOT}/drivers/simulator/src" "${HARNESS_ROOT}/tests/plugins/misc")
  target_compile_definitions(driver_simulator_vfs.${behavior} PRIVATE FS_ENABLE=32)
  if(MINGW)
    target_compile_options(driver_simulator_vfs.${behavior} PRIVATE -include "${HARNESS_ROOT}/tests/include/windows_string_compat.h")
  endif()
endforeach()
set_source_files_properties("${HARNESS_ROOT}/drivers/simulator/src/fs_posix.c" PROPERTIES COMPILE_OPTIONS -Wno-unused-parameter)
# The main harness also keeps fixture warnings strict without promoting CORE warnings.
set_source_files_properties("${COMPONENT_CORE_ROOT}/vfs.c" "${COMPONENT_CORE_ROOT}/strutils.c" PROPERTIES COMPILE_OPTIONS -Wno-error)

set_tests_properties(driver_simulator_vfs.nested_listing driver_simulator_vfs.remount_missing driver_simulator_vfs.pending_truncate PROPERTIES WILL_FAIL TRUE LABELS known_bug)
