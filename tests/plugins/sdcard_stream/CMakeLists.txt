cmake_minimum_required(VERSION 3.20)
project(grblhal_sdcard_stream_tests LANGUAGES C)
include(../../components.cmake)
foreach(behavior job_completion line_endings error_recovery reset tool_change rejections listing dump progress input_filter connection_change macro_repeat dump_unterminated)
 component_case(plugin_sdcard_stream.${behavior} ${behavior}.c sd_host.c
  "${HARNESS_ROOT}/plugins/sdcard/fs_stream.c" "${HARNESS_ROOT}/plugins/sdcard/macros.c"
  "${COMPONENT_CORE_ROOT}/vfs.c" "${COMPONENT_CORE_ROOT}/fs_embedded.c" "${COMPONENT_CORE_ROOT}/stream.c" "${COMPONENT_CORE_ROOT}/stream_file.c"
  "${COMPONENT_CORE_ROOT}/strutils.c" "${COMPONENT_CORE_ROOT}/nuts_bolts.c")
 target_compile_definitions(plugin_sdcard_stream.${behavior} PRIVATE FF_FS_READONLY=1 FF_FS_MINIMIZE=1 NGC_EXPRESSIONS_ENABLE=0)
 target_include_directories(plugin_sdcard_stream.${behavior} PRIVATE "${HARNESS_ROOT}/plugins/sdcard")
 if(MINGW)
  target_compile_options(plugin_sdcard_stream.${behavior} PRIVATE -include "${HARNESS_ROOT}/tests/include/windows_string_compat.h")
 endif()
endforeach()
set_source_files_properties("${HARNESS_ROOT}/plugins/sdcard/fs_stream.c" "${HARNESS_ROOT}/plugins/sdcard/macros.c" "${COMPONENT_CORE_ROOT}/vfs.c" "${COMPONENT_CORE_ROOT}/fs_embedded.c" "${COMPONENT_CORE_ROOT}/stream.c" "${COMPONENT_CORE_ROOT}/stream_file.c" "${COMPONENT_CORE_ROOT}/strutils.c" PROPERTIES COMPILE_OPTIONS -Wno-error)

set_tests_properties(plugin_sdcard_stream.line_endings plugin_sdcard_stream.dump PROPERTIES WILL_FAIL TRUE LABELS known_bug)
