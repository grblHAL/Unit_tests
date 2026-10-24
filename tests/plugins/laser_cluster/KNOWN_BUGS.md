# Known defects and scope

No runtime defect is currently classified for these valid default cluster streams.
Original laser source 26934c6c9607e0b5ba4a711516a60d4657bf142c and CORE
b01f481072edecac33d5e40c25869359a5b3fa1f are unchanged.

The original LightBurn decoder executes through public stream/report/reset
hooks and actual CORE numeric helpers. Source read callbacks and stream/file
selection are simulated driver boundaries; file mode does not mount a physical
filesystem here. These are byte/acknowledgement transformation tests, not full
G-code parser/motion or LightBurn hardware integration. Default16-value capacity
and unscaled S-values are compiled; S scaling and other sizes remain.

Cases cover X/Y and negative movement division, feed preservation, equal/different
power, restoration, file/normal reads, paired endings, one ACK per cluster,
fragment reset, stream changes and report chaining. Original source warnings
remain visible under -Wno-error while fixtures keep -Werror. No sanitizer
allowances or repository-wide coverage claim.
