# ADR-0003 — `dkaukov/esp32-afsk` as the MVP AFSK candidate

- **Status:** Accepted for validation
- **Date:** 2026-09-09
- **Scope:** RadioNode Box / legacy-radio adapter

## Context

RadioNode BR needs an AFSK 1200 modem path for analog radios that do not expose a native TNC. The first MVP should validate the architecture before the project invests in a custom modem implementation or PCB.

The upstream `dkaukov/esp32-afsk` project already provides an ESP32-oriented AFSK modem helper library with:

- demodulation from PCM samples;
- modulation to PCM samples;
- ESP32/ESP32-S3 as explicit target platforms;
- native decoder tests;
- an embedded ESP32 benchmark;
- a KISS TNC example using SA818/DRA818-style radio hardware and audio/PTT switching.

This maps closely to the RadioNode Box boundary: radio audio/PTT on one side and AX.25/KISS toward host applications on the other.

## Decision

Adopt `dkaukov/esp32-afsk` as the **primary AFSK candidate for the RadioNode-BR MVP validation**, with this reference path:

```text
VHF/UHF radio
    ↕ audio + PTT
ESP32-S3 / RadioNode Box
    ↕ esp32-afsk (AFSK 1200)
AX.25
    ↕
KISS
    ↕ BLE or USB
RadioLink Mobile / host software
```

The first validation sequence is:

1. build and run upstream native tests without RadioNode-specific changes;
2. build the KISS TNC example for an ESP32-S3-compatible target;
3. validate RX from recorded/known AFSK fixtures before live RF;
4. validate TX waveform generation into a dummy/test audio path before keying a radio;
5. connect audio/PTT hardware and validate simplex RX/TX on the bench;
6. expose the resulting TNC over USB first, then BLE, using KISS as the host contract;
7. integrate that KISS endpoint with RadioLink Mobile without coupling RadioLink protocol code to the modem implementation.

## Licensing boundary

The upstream repository is licensed under **GPL-3.0**, while RadioNode BR is currently **Apache-2.0**.

Therefore this ADR does **not** authorize copying or vendoring GPL source into the Apache-licensed RadioNode BR tree as if it were Apache code. During MVP validation, `esp32-afsk` must remain clearly identified as an external upstream dependency/reference with its own license and copyright notices.

Before distributing a combined firmware derived from or statically incorporating GPL-covered code, the project must explicitly decide and document the resulting licensing/distribution model. If keeping an Apache-only firmware component is a requirement, alternatives include a clean-room modem implementation or another dependency with compatible licensing.

## Consequences

### Positive

- avoids writing an AFSK modem from zero before validating the product architecture;
- gives the MVP a concrete RX/TX implementation and test corpus;
- aligns naturally with ESP32-S3 and the KISS boundary already selected by RadioNode/RadioLink;
- lets RadioLink Mobile remain modem-agnostic.

### Constraints

- live RX/TX still requires physical validation;
- PTT fail-safe and maximum-TX timeout remain RadioNode responsibilities even if the modem library works;
- audio levels, filtering, sample path and radio-specific cabling remain hardware concerns;
- upstream GPL-3.0 licensing must remain explicit and cannot be silently absorbed into the Apache-2.0 project.

## Exit criteria for MVP candidate status

`esp32-afsk` may be promoted from candidate to the reference RadioNode AFSK implementation only after:

- deterministic fixture decode passes on the chosen ESP32-S3 target;
- TX samples are validated before RF keying;
- bench RX/TX succeeds through the intended audio/PTT interface;
- KISS transport works through the selected USB/BLE bridge;
- PTT fail-safe and timeout behavior are independently verified;
- the distribution/licensing strategy is documented.
