# Confirmed defects: keep each regression and remove its block when fixed.
# Dates, reproductions, and removal instructions: KNOWN_BUGS.md

if(TEST delta.unreachable_cartesian_target_rejected)
  set_tests_properties(delta.unreachable_cartesian_target_rejected PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST rtcp_ac.rotary_segment_endpoint)
  set_tests_properties(rtcp_ac.rotary_segment_endpoint PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.m68_preserves_fractional_output)
  set_tests_properties(gcode.m68_preserves_fractional_output PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Spindle listing uses the registered slot settings.
# The test follows supported setup and passes normally.
# No known-bug exception is needed.

# MPG commands intentionally allow one outstanding command at a time.
# Covered by stream.mpg_buffered_commands_wait_for_response.
# This is an ordinary passing test of the supported command/response protocol.

# ngc_flowctrl.named_macro_call_opens_file_and_sets_local_arguments
# Uses a static backend to test EOF restoration independently of file freeing.
# Ordinary passing test; no known-bug exception.

# ngc_flowctrl.named_macro_eof_restores_caller_stream_and_parameter_scope
# Uses a static backend to test EOF restoration independently of file freeing.
# Ordinary passing test; no known-bug exception.

if(TEST ngc_flowctrl.named_macro_return_closes_file_and_restores_caller_scope)
  set_tests_properties(ngc_flowctrl.named_macro_return_closes_file_and_restores_caller_scope PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_flowctrl.named_macro_return_preserves_subroutine_callback_lifetime)
  set_tests_properties(ngc_flowctrl.named_macro_return_preserves_subroutine_callback_lifetime PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_flowctrl.named_macro_end_sub_preserves_subroutine_callback_lifetime)
  set_tests_properties(ngc_flowctrl.named_macro_end_sub_preserves_subroutine_callback_lifetime PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_flowctrl.named_macro_error_preserves_subroutine_callback_lifetime)
  set_tests_properties(ngc_flowctrl.named_macro_error_preserves_subroutine_callback_lifetime PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# M72 leaves parser feed override control disabled; verified 2026-10-13 on e65020a.
if(TEST ngc_params.m72_restores_feed_and_rapid_overrides_after_m50_disable)
  set_tests_properties(ngc_params.m72_restores_feed_and_rapid_overrides_after_m50_disable PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Restored archived regression; still reproduced on Terje e65020a (2026-10-13).
if(TEST gcode.file_percent_marker_after_unmarked_start_is_rejected)
  set_tests_properties(gcode.file_percent_marker_after_unmarked_start_is_rejected PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# $G reports lathe roughing modes as probe codes; verified 2026-10-13 on e65020a.
if(TEST lathe_ngc.roughing_modal_report_uses_g71)
  set_tests_properties(lathe_ngc.roughing_modal_report_uses_g71 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.roughing_modal_report_uses_g71_1)
  set_tests_properties(lathe_ngc.roughing_modal_report_uses_g71_1 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.roughing_modal_report_uses_g71_2)
  set_tests_properties(lathe_ngc.roughing_modal_report_uses_g71_2 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.roughing_modal_report_uses_g72)
  set_tests_properties(lathe_ngc.roughing_modal_report_uses_g72 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.roughing_modal_report_uses_g72_1)
  set_tests_properties(lathe_ngc.roughing_modal_report_uses_g72_1 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.roughing_modal_report_uses_g72_2)
  set_tests_properties(lathe_ngc.roughing_modal_report_uses_g72_2 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Scaling factors are dimensionless; report conversions verified on e65020a.
if(TEST report.scaling_parameter_report_keeps_dimensionless_factors_in_inches)
  set_tests_properties(report.scaling_parameter_report_keeps_dimensionless_factors_in_inches PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.scaling_parameter_report_does_not_double_diameter_mode_factor)
  set_tests_properties(lathe_ngc.scaling_parameter_report_does_not_double_diameter_mode_factor PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Named motion parameter exposes internal enums; verified 2026-10-13 on e65020a.
if(TEST lathe_ngc.named_motion_mode_reports_g71)
  set_tests_properties(lathe_ngc.named_motion_mode_reports_g71 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.named_motion_mode_reports_g71_1)
  set_tests_properties(lathe_ngc.named_motion_mode_reports_g71_1 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.named_motion_mode_reports_g72)
  set_tests_properties(lathe_ngc.named_motion_mode_reports_g72 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.named_motion_mode_reports_g38_2)
  set_tests_properties(ngc_params.named_motion_mode_reports_g38_2 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.named_motion_mode_reports_g38_3)
  set_tests_properties(ngc_params.named_motion_mode_reports_g38_3 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.named_motion_mode_reports_g38_4)
  set_tests_properties(ngc_params.named_motion_mode_reports_g38_4 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.named_motion_mode_reports_g38_5)
  set_tests_properties(ngc_params.named_motion_mode_reports_g38_5 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.named_motion_mode_reports_quadratic_spline_code)
  set_tests_properties(ngc_params.named_motion_mode_reports_quadratic_spline_code PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
