# ADR-0004 — Accessibility as a first-class cross-cutting capability

- **Status:** Accepted
- **Date:** 2026-09-12
- **Scope:** RadioNode Core, RadioNode Box and host integrations

## Context

RadioNode BR is intended for field, emergency and off-grid operation. Requiring visual interaction for basic status, safety alerts or operation would unnecessarily exclude blind and low-vision radio amateurs and would also make the platform less usable in situations where looking at a display is impractical.

A concrete open-source reference exists in [`jewelux/talking-swr-meter-LX1WJ`](https://github.com/jewelux/talking-swr-meter-LX1WJ). That project demonstrates a screenless ESP32-S3 radio accessory using:

- speech through I2S audio;
- Morse through a buzzer;
- continuous pitch feedback for tuning;
- a small physical-button interface;
- local operation without requiring a display.

Its firmware is GPL-3.0 and its documentation is CC BY-SA 4.0. RadioNode BR is Apache-2.0, so this ADR adopts interaction and architectural patterns as references without authorizing code copying or vendoring.

## Decision

Accessibility becomes a **first-class cross-cutting capability** of RadioNode BR.

The project will implement a `RadioNode Accessibility Engine` as a consumer of semantic events emitted by the core, transports, drivers and local hardware telemetry.

Reference boundary:

```text
Radio / sensors / drivers
          │
          ▼
RadioNode Core + telemetry
          │ semantic events
          ▼
Accessibility Engine
   ├── speech / I2S
   ├── Morse
   ├── tones
   └── host/mobile accessibility
```

The engine is not a transport, modem, RF protocol or replacement for host accessibility APIs.

The initial design rules are:

1. essential status and alerts must be representable without a display;
2. accessibility outputs must be non-blocking and must not interfere with RF timing or safety mechanisms;
3. PTT fail-safe, watchdog and maximum-TX timeout always have priority over speech, Morse or tones;
4. events should remain semantic and structured; localization and phrase generation belong in the accessibility layer;
5. essential feedback must be able to operate offline;
6. `pt-BR` is the first localization profile;
7. speech, Morse and tonal feedback are complementary modalities rather than mutually exclusive implementations;
8. local audio hardware is optional and may coexist with accessibility provided by RadioLink Mobile or another host.

## Initial event classes

### Critical

Examples:

- PTT timeout;
- PTT fault latch;
- hardware fault;
- critical battery;
- overtemperature when available.

### Operational

Examples:

- mode change;
- transport/radio connected or disconnected;
- GPS acquired or lost;
- frequency/channel change when available;
- beacon transmitted;
- message received;
- acknowledgement received;
- KISS host connection state.

### Informational

Examples:

- battery level;
- active callsign/profile;
- firmware version;
- pending message count;
- gateway/network status.

SWR and RF power announcements are not mandatory RadioNode Box functions. They become eligible events only when suitable measurement hardware is present.

## Hardware direction

For a local-audio prototype, the preferred low-complexity path is:

```text
ESP32-S3 → I2S → MAX98357A (or equivalent) → speaker
          └──── PWM/GPIO → optional buzzer
```

Physical controls may be implemented with a few dedicated buttons or an ADC resistor ladder after pin/resource review.

This does not modify the current F4 promotion gate: AFSK RX/TX and safe physical PTT validation remain the immediate RadioNode Box milestone.

## Software consequences

The core/event model should eventually expose an accessibility-safe semantic event contract rather than pre-rendered sentences.

Example conceptual event:

```text
kind = frequency_changed
priority = operational
params = { hz: 146950000 }
```

The `pt-BR` accessibility profile may render the event as speech, Morse, tones or host notification according to policy.

The engine requires:

- priority queues;
- interrupt/cancel behavior;
- rate limiting;
- deduplication/obsolescence handling;
- localization;
- modality policy;
- offline fallback behavior.

## Licensing boundary

No source from `talking-swr-meter-LX1WJ` is incorporated by this decision.

If a future implementation reuses GPL-3.0 firmware code, the project must first document the distribution and licensing impact in a dedicated ADR. Until then, LX1WJ is an architectural and interaction reference only.

## Consequences

### Positive

- accessibility is designed before UI and hardware contracts become rigid;
- the same events can feed local audio and mobile accessibility;
- screenless operation also improves field usability for sighted operators;
- the design remains transport-agnostic;
- safety alerts gain a structured presentation path without becoming part of the safety mechanism itself.

### Constraints

- additional I2S/GPIO/RAM/flash resources may be needed on hardware profiles that provide local speech;
- audio scheduling must remain isolated from RF-critical paths;
- a limited offline vocabulary may be preferable to unrestricted TTS in the first implementation;
- accessibility must be tested as behavior, not accepted merely because features exist in code.

## Validation criteria

This decision is considered implemented when at least one RadioNode profile demonstrates:

- essential operation without display for a defined task set;
- deterministic critical/operational event prioritization;
- offline speech or equivalent accessible feedback;
- Morse or tonal fallback for selected events;
- no interference with PTT fail-safe or AFSK processing;
- an eyes-free validation script;
- host controls with correct screen-reader semantics when a host UI is present.

Detailed design: [`../accessibility.md`](../accessibility.md).
