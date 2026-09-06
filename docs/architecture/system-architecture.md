# Arquitetura do Sistema

## Objetivo

O RadioNode BR é uma plataforma modular para nós de comunicação radioamadora. O núcleo deve permanecer independente de uma rede específica e permitir composição de perfis como repetidora analógica, APRS, telemetria, LoRa e gateways de voz/dados.

## Camadas

### 1. Controlador embarcado — ESP32-S3
Responsabilidades:
- leitura de COS/COR;
- controle de PTT;
- anti-kerchunk, hang/hold time, TOT e calm-down;
- boot inhibit e watchdog;
- telemetria local;
- GPS, LoRa e display;
- configuração local e diagnóstico;
- arbitragem final de qualquer solicitação de TX.

O ESP32 não deve depender do Linux para manter a repetidora em estado seguro.

### 2. Gateway Linux
Plataformas alvo iniciais:
- Raspberry Pi 3B+;
- DigiPi;
- Raspberry Pi OS/Debian compatível.

Responsabilidades:
- Direwolf;
- APRS-IS;
- SvxLink/EchoLink;
- logs e observabilidade;
- dashboard;
- API/agent local;
- adaptadores para redes externas.

### 3. Redes e adaptadores
Cada rede é tratada como integração independente. O core não deve assumir APRS, EchoLink, BrandMeister ou qualquer outra rede como requisito obrigatório.

Adaptadores previstos:
- APRS / Direwolf / APRS-IS;
- EchoLink / SvxLink;
- DMR / MMDVM / BrandMeister;
- XLX/YSF e outros modos digitais em fases posteriores;
- LoRa local para telemetria e experimentação.

## Fluxo de controle de repetidora

```text
Rádio RX ── COS/COR ──> ESP32 ── PTT ──> Rádio TX
    │                                   ▲
    └──────────── caminho de áudio ─────┘
```

O caminho de áudio e o caminho de controle são tratados separadamente.

## Fluxo APRS

```text
144.390 MHz
    │
Rádio VHF
    │
Interface de áudio
    │
Direwolf
    │
Gateway Linux
    │
APRS-IS
```

LoRa 433 MHz não é tratado como substituto do APRS VHF.

## Fluxo EchoLink

```text
Internet
   │
EchoLink
   │
SvxLink
   │
Interface de áudio
   │
Repetidora
```

Solicitações de transmissão originadas no Linux devem passar pela autoridade PTT do ESP32.

## Comunicação ESP32 ↔ Linux

Primária: USB/serial.

Secundária: Wi-Fi para configuração, diagnóstico ou fallback.

O protocolo deve transportar:
- status;
- eventos;
- telemetria;
- solicitações de TX;
- respostas de autorização/negação;
- comandos administrativos seguros.

## Princípio de segurança

A falha deve tender ao estado seguro:

> reset, travamento, boot incompleto ou ausência do controlador não podem deixar o transmissor chaveado.
