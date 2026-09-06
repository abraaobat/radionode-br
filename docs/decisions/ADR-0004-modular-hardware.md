# ADR-0004 — Modular hardware

- Status: Accepted
- Date: 2026-09-04

## Context

Nem todo nó precisa de GPS, LoRa, display, APRS, EchoLink ou voz digital.

## Decision

GPS, SX1278, display e demais periféricos serão tratados como módulos opcionais sobre um núcleo comum.

## Consequences

- Perfis de hardware podem ser menores e mais baratos.
- O firmware deve detectar ou configurar capacidades presentes.
- A futura PCB deve preservar modularidade sempre que isso não comprometer confiabilidade e custo.
