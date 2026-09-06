# ADR-0002 — ESP32 as final PTT authority

- Status: Accepted
- Date: 2026-09-04

## Context

Serviços Linux como SvxLink podem precisar iniciar uma transmissão, mas o nó também precisa respeitar TOT, temperatura, falhas de alimentação, bloqueios administrativos e outras proteções locais.

## Decision

O ESP32-S3 será a autoridade final sobre PTT. O Linux poderá solicitar transmissão, mas o ESP32 decidirá se a solicitação pode ser atendida.

## Consequences

- O Linux não deve contornar o controlador para chavear PTT diretamente.
- Negativas de TX devem ser explícitas e diagnosticáveis.
- A repetidora permanece protegida mesmo quando serviços de rede falham ou se comportam incorretamente.
