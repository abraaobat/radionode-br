# ADR-0002 — RadioNode Core multimodo e transportes de primeira classe

- **Status:** Accepted
- **Date:** 2026-09-05

## Contexto

A arquitetura inicial do RadioNode BR foi definida a partir de uma combinação ESP32 + Linux/DigiPi, com APRS e LoRa tratados como domínios separados. A investigação de rádios com TNC/KISS Bluetooth integrado, rádios DMR com GPS/modem próprio e redes LoRa/Meshtastic mostrou que o projeto pode ser mais útil se aplicações e serviços não dependerem de um único meio RF.

Também ficou claro que nem todo rádio precisa de uma RadioNode Box: alguns equipamentos já expõem KISS/AX.25, enquanto outros oferecem DMR Data/SMS ou somente áudio/PTT.

## Decisão

O RadioNode BR adotará uma arquitetura **transport-agnostic**.

O núcleo comum representa identidade, mensagens, posição, contatos, marcadores, telemetria, filas e políticas de entrega. Meios de comunicação entram através de uma API de transporte.

São considerados transportes de primeira classe:

1. **VHF/UHF + AX.25/KISS/APRS**;
2. **DMR Data/SMS**, inicialmente experimental;
3. **LoRa/Meshtastic**;
4. **IP**, opcional para gateways e serviços.

ATAK/CoT, APRS-IS e TAK Server são integrações/aplicações e não transportes RF canônicos.

## Classes de rádio

A arquitetura reconhece três classes iniciais:

### Native KISS

Rádios com TNC/KISS acessível diretamente. Devem dispensar a RadioNode Box sempre que possível.

### DMR native modem

Rádios com modem DMR/GPS próprio. Devem usar transporte DMR específico quando houver API programática bidirecional disponível.

### Legacy/generic analog

Rádios sem TNC acessível. Devem usar a RadioNode Box para áudio, PTT, modem, KISS e conectividade local.

## Consequências

### Positivas

- o core não fica preso a um rádio ou fabricante;
- rádios com KISS nativo reduzem custo e hardware externo;
- rádios analógicos baratos continuam suportáveis via RadioNode Box;
- DMR pode ser explorado sem forçar equivalência com AX.25;
- LoRa/Meshtastic passa a coexistir com VHF/DMR;
- gateways podem escolher ou interligar transportes de forma explícita;
- ATAK/CoT pode operar sobre diferentes meios usando payload compacto.

### Custos

- exige contratos claros entre Core, Transport e Driver;
- cada transporte precisa respeitar seus próprios limites de payload, latência, duty cycle e regulamentação;
- bridges exigem políticas para evitar loops e retransmissão indevida;
- DMR ainda depende de validação de APIs em hardware real;
- interoperabilidade deve ser comprovada em bancada e campo.

## Não objetivos

- declarar todos os transportes igualmente maduros desde o início;
- transmitir CoT/XML bruto obrigatoriamente por RF;
- criar bridge automática e irrestrita entre todas as redes;
- assumir que qualquer repetidora de voz suporta packet/dados;
- transformar LoRa em substituto de APRS/VHF ou vice-versa.

## Direção de implementação

```text
Applications / Integrations
          │
          ▼
    RadioNode Core
          │
   Transport API
     /    |    \
 AX.25   DMR   LoRa
   │      │      │
Drivers / adapters / radios
```

O transporte VHF/AX.25/KISS será o primeiro baseline estável. LoRa/Meshtastic será desenvolvido em paralelo como transporte separado. DMR permanecerá experimental até comprovação de envio e recepção programática de dados em tempo real.
