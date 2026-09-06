# ADR-0007 — Validate with modules before a custom PCB

- Status: Accepted
- Date: 2026-09-04

## Context

O projeto ainda está validando pinagem, interfaces de rádio, áudio, proteção, telemetria e periféricos. Uma PCB definitiva agora congelaria decisões prematuras.

## Decision

As versões V0.x serão prototipadas com módulos comerciais e interfaces de bancada. A PCB própria será desenhada somente após validação funcional das interfaces críticas.

## Consequences

- Mudanças de arquitetura permanecem baratas nas fases iniciais.
- A documentação de pinagem e interfaces deve preceder o layout da PCB.
- A fase V0.8 consolida esquemático, BOM e placa própria.
