# ADR-0006 — Fail-safe PTT

- Status: Accepted
- Date: 2026-09-04

## Context

Uma falha de firmware, reset ou perda de alimentação não pode deixar o transmissor chaveado.

## Decision

A interface PTT deve ser fail-safe: ausência de comando válido, boot incompleto, reset ou falha do controlador deve resultar em PTT OFF. A solução deve combinar firmware com desenho elétrico apropriado.

## Consequences

- PTT não pode depender apenas de estado de software após boot.
- A interface real de rádio deverá usar estágio de chaveamento/isolamento apropriado.
- Proteções de hardware adicionais poderão ser incorporadas nas revisões seguintes.
