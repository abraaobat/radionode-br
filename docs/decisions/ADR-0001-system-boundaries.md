# ADR-0001 — System boundaries between radio control and network services

- **Status:** Accepted
- **Date:** 2026-09-04

## Context

O RadioNode BR combina controle de rádio, periféricos locais, processamento APRS e integrações de rede. Colocar todas essas responsabilidades no mesmo runtime aumentaria o acoplamento e poderia transformar falhas de serviços Linux ou de rede em risco operacional para funções críticas de transmissão.

## Decision

O sistema será dividido em duas fronteiras principais:

1. **ESP32-S3 — radio-control authority**
   - autoridade final sobre PTT;
   - leitura de COS/COR;
   - timers e intertravamentos;
   - watchdog e comportamento fail-safe;
   - telemetria/periféricos locais apropriados.

2. **Linux / Raspberry Pi / DigiPi — gateway and services**
   - Dire Wolf/KISS;
   - APRS/APRS-IS;
   - serviços de rede e voz;
   - logs, dashboard e integrações externas.

Serviços Linux podem solicitar transmissão, mas não podem contornar as proteções locais do controlador.

APRS, EchoLink, BrandMeister, XLX, YSF e outras redes serão integradas por módulos/adapters independentes. LoRa permanece uma integração distinta de APRS.

## Consequences

### Positive

- reduz acoplamento entre RF crítica e serviços de rede;
- facilita fail-safe de PTT;
- permite trocar DigiPi por outro Linux compatível;
- permite adicionar/remover redes sem alterar o núcleo de controle;
- melhora testabilidade e diagnóstico.

### Trade-offs

- exige protocolo explícito ESP32 ↔ Linux;
- aumenta o número de componentes a integrar e versionar;
- requer testes de comportamento em desconexão e versões incompatíveis.

## Follow-up

O protocolo físico e lógico entre ESP32 e Linux deve ser definido em ADR posterior somente após comparação das opções e validação de bancada.
