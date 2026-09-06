# ADR-0001 — Network-agnostic core

- Status: Accepted
- Date: 2026-09-04

## Context

O RadioNode BR pode operar com APRS, EchoLink, redes de voz digital e LoRa. Acoplar o núcleo a uma única rede reduziria a reutilização do hardware e do software.

## Decision

O núcleo do RadioNode BR será agnóstico de rede. Protocolos e redes externas serão implementados por adaptadores independentes.

## Consequences

- APRS, EchoLink, BrandMeister, XLX/YSF e integrações futuras podem evoluir separadamente.
- Um nó pode habilitar somente os adaptadores necessários.
- O protocolo interno ESP32 ↔ Linux não deve depender de semântica específica de uma rede externa.
