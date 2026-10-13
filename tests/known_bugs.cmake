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
