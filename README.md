# RadioNode BR

Plataforma modular e open source para construção de nós de comunicação radioamadora interoperáveis, com foco inicial no ecossistema brasileiro.

## Visão

O RadioNode BR separa funções críticas de rádio das funções de rede e serviços:

- **ESP32-S3**: controle determinístico, COS/COR, PTT, temporização, proteções, telemetria e periféricos locais.
- **Linux / Raspberry Pi / DigiPi**: Direwolf, APRS-IS, SvxLink, EchoLink, serviços, logs, dashboard e integrações de rede.

O projeto é **network-agnostic**: APRS, EchoLink, BrandMeister, XLX, YSF e outras redes são tratadas como integrações independentes, não como dependências do núcleo.

## Hardware de referência V0.1

- ESP32-S3 N16R8
- SX1278 LoRa 433 MHz
- GPS u-blox NEO-6M
- display ST7789 240x240 (planejado)
- Raspberry Pi 3B+ com DigiPi para o gateway Linux inicial

## Princípios

1. **PTT fail-safe**: reset, travamento ou ausência do controlador deve resultar em TX desligado.
2. **ESP32 como autoridade final de PTT**: serviços Linux podem solicitar TX, mas não contornam as proteções locais.
3. **APRS e LoRa são redes distintas**: LoRa 433 MHz não substitui APRS VHF.
4. **Modularidade**: GPS, LoRa, display, APRS, EchoLink e voz digital podem ser opcionais.
5. **DigiPi suportado, não obrigatório**: o gateway deve poder rodar também em Raspberry Pi OS/Debian compatível.
6. **Hardware validado antes da PCB própria**: as versões V0.x usam módulos e interfaces de bancada antes do desenho da placa definitiva.

## Status

Projeto em bootstrap. A arquitetura, roadmap, ADRs e interfaces iniciais estão sendo formalizados antes do desenvolvimento do firmware e da placa.

## Ecossistema relacionado

- `aprsd-smsbr-plugin`: integração APRS/APRSD com SMS brasileiro, tratada como componente externo integrável ao RadioNode BR.

> O RadioNode BR é um projeto experimental de radioamadorismo. Operação em RF deve respeitar a regulamentação aplicável, o licenciamento da estação e as regras de cada rede integrada.
