# RadioNode BR — Arquitetura

## Objetivo

O RadioNode BR é uma plataforma modular para construção de nós de comunicação radioamadora interoperáveis, com foco inicial no ecossistema brasileiro.

A arquitetura separa funções determinísticas e de segurança de rádio das funções de rede, serviços e integrações.

## Fronteira principal

```text
┌──────────────────────────────────────────┐
│ ESP32-S3                                 │
│                                          │
│ COS/COR · PTT · timers · protections     │
│ GPS · local telemetry · peripherals      │
│                                          │
│ authority final over PTT                 │
└───────────────────┬──────────────────────┘
                    │ interface versionada
┌───────────────────▼──────────────────────┐
│ Linux / Raspberry Pi / DigiPi            │
│                                          │
│ Dire Wolf · APRS-IS · SvxLink            │
│ EchoLink · services · logs · dashboard   │
│ network integrations                     │
└──────────────────────────────────────────┘
```

## Princípios arquiteturais

1. **Fail-safe em transmissão.** Reset, travamento ou ausência do controlador deve resultar em TX desligado.
2. **ESP32 como autoridade final de PTT.** O Linux pode solicitar transmissão, mas não pode contornar as proteções locais.
3. **Separação entre rádio e rede.** Falhas de Internet, serviços ou processos Linux não devem remover proteções críticas de RF.
4. **Integrações desacopladas.** APRS, EchoLink, BrandMeister, XLX, YSF e futuras redes entram por adapters/módulos, não no núcleo.
5. **APRS e LoRa permanecem domínios distintos.** LoRa 433 MHz não é tratado como substituto de APRS VHF.
6. **DigiPi é suportado, não obrigatório.** O gateway deve poder evoluir para Raspberry Pi OS/Debian compatível.
7. **Hardware modular primeiro.** V0.x deve validar módulos e interfaces de bancada antes de uma PCB própria.

## Componentes iniciais

### Controlador de rádio

Responsabilidade prevista do ESP32-S3:

- leitura de COS/COR;
- controle final de PTT;
- temporização e timeout de transmissão;
- intertravamentos e estados de falha;
- telemetria local;
- GPS e periféricos locais;
- interface com display;
- integração opcional com módulo LoRa.

### Gateway Linux

Responsabilidade prevista do Linux/Raspberry Pi/DigiPi:

- Dire Wolf e KISS;
- APRS e APRS-IS;
- serviços de voz/rede quando habilitados;
- logs e observabilidade;
- dashboard;
- configuração de integrações;
- comunicação com serviços externos.

## Hardware de referência V0.1

- ESP32-S3 N16R8;
- SX1278 LoRa 433 MHz;
- GPS u-blox NEO-6M;
- display ST7789 240x240, planejado;
- Raspberry Pi 3B+ com DigiPi como gateway Linux inicial.

## Interfaces

As interfaces entre ESP32, gateway Linux e módulos externos devem ser explicitamente versionadas antes de se tornarem dependências estáveis.

Nenhum protocolo físico ou formato de mensagem é declarado canônico neste estágio. Essa decisão deve ser registrada por ADR após validação em bancada.

## Ecossistema relacionado

`aprsd-smsbr-plugin` é tratado como componente externo integrável. O RadioNode BR pode consumi-lo ou documentar sua integração, mas não deve incorporar seu domínio ao núcleo.
