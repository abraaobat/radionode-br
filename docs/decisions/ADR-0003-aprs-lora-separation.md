# ADR-0003 — APRS VHF and LoRa are separate networks

- Status: Accepted
- Date: 2026-09-04

## Context

O protótipo usa SX1278 em 433 MHz e também prevê integração APRS. Apesar de ambos transportarem dados por RF, pertencem a arquiteturas e ecossistemas distintos.

## Decision

O RadioNode BR tratará APRS VHF e LoRa 433 MHz como subsistemas independentes. LoRa não será apresentado como substituto de APRS.

## Consequences

- APRS usa rádio/interface apropriados e Direwolf/APRS-IS quando aplicável.
- SX1278 permanece destinado a telemetria, experimentação e possíveis links locais próprios.
- Integrações entre os dois mundos, se existirem, ocorrerão em uma camada explícita de gateway.
