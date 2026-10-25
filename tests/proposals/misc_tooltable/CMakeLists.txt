cmake_minimum_required(VERSION 3.20)
project(grblhal_tooltable_proposal LANGUAGES C)
get_filename_component(HARNESS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../.." ABSOLUTE)
include("${HARNESS_ROOT}/tests/components.cmake")

foreach(behavior load_entries save_reload clear_reload missing_file open_recovery hooks_reports random_sparse)
  set(target plugins_misc.tooltable_${behavior})
  component_case(${target} ${behavior}.c table_host.c "${COMPONENT_CORE_ROOT}/vfs.c" "${COMPONENT_CORE_ROOT}/strutils.c" "${COMPONENT_CORE_ROOT}/nuts_bolts.c" "${HARNESS_ROOT}/plugins/misc/tooltable.c")
  target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
  target_compile_definitions(${target} PRIVATE TOOLTABLE_ENABLE=1)
  if(WIN32)
    target_compile_definitions(${target} PRIVATE NO_OLDNAMES=1)
  endif()
endforeach()
set_source_files_properties("${HARNESS_ROOT}/plugins/misc/tooltable.c" PROPERTIES COMPILE_OPTIONS "-Wno-unused-parameter;-Wno-missing-field-initializers")
set_source_files_properties("${COMPONENT_CORE_ROOT}/vfs.c" PROPERTIES COMPILE_OPTIONS "-Wno-unused-parameter;-Wno-sign-compare")
# random_sparse is an unverified candidate: classify only after source compatibility
# is repaired and actual execution establishes its outcome.
