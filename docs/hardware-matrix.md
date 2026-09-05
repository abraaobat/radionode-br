# RadioNode BR — Matriz de hardware candidato

Esta matriz registra plataformas candidatas para desenvolvimento e testes. **Candidato não significa suportado/validado.** Promoção para suporte oficial exige testes reproduzíveis em hardware real.

## HTs Native KISS / AX.25

| Rádio | Papel | Recursos relevantes | Status no RadioNode |
|---|---|---|---|
| VGC/Vero VR-N76 | plataforma Native KISS aberta | GPS, APRS, Bluetooth, KISS/AX.25 | prioridade alta para validação |
| BTECH UV-PRO | benchmark | GPS, APRS, Bluetooth KISS, ecossistema TAK existente | prioridade alta / referência |
| Radtel RT-660 | opção econômica | GPS/BDS, APRS, Bluetooth/KISS anunciado e observado em software de terceiros | prioridade alta para teste |
| Radioddity GA-5WB | interoperabilidade da família | GPS, APRS, Bluetooth, ecossistema compartilhado | prioridade média-alta |

## DMR

| Rádio | Papel | Recursos relevantes | Status no RadioNode |
|---|---|---|---|
| Baofeng DM-32UV | primeiro candidato RadioNode-DMR | DMR, GPS/BDS, Digital APRS, SMS/Data | pesquisa; API em tempo real ainda precisa ser comprovada |

O transporte DMR não deve ser considerado equivalente ao AX.25/KISS. O objetivo é explorar o modem digital nativo do rádio através de uma interface programática própria.

## Legacy / generic analog

| Rádio | Papel | Recursos relevantes | Status no RadioNode |
|---|---|---|---|
| Quansheng K1 | plataforma inicial RadioNode Box | FM VHF/UHF, baixo custo, áudio/PTT acessíveis | prioridade alta; rádio já disponível para bancada |
| Quansheng K5 e variantes | expansão de compatibilidade | FM VHF/UHF, comunidade/firmware | candidato |
| Outros HTs/móveis analógicos | compatibilidade universal | áudio RX/TX + PTT | futuro, via cabos/adapters |

## Rádios móveis / base

| Rádio | Papel | Recursos relevantes | Status no RadioNode |
|---|---|---|---|
| Radioddity DB50-B | RadioNode Mobile / Gateway | alta potência, GPS/APRS, Bluetooth/KISS | candidato prioritário |
| VGC/Vero VR-N7600 | RadioNode Mobile / Gateway | alta potência, GPS/APRS, Bluetooth/KISS | candidato prioritário |

## Gateways e adapters

| Plataforma | Papel |
|---|---|
| Raspberry Pi 3B+ + DigiPi | gateway Linux inicial |
| Dire Wolf | KISS/AX.25/APRS software modem e referência de interoperabilidade |
| ESP32-S3 | RadioNode Box, RadioNode Link e bridges experimentais |
| SX1278 LoRa 433 MHz | protótipo de transporte LoRa |
| Meshtastic-compatible nodes | transporte mesh / interoperabilidade LoRa |

## Estratégia de validação

A primeira matriz mínima de testes deve cobrir quatro hipóteses diferentes:

1. **Native KISS:** um VR-N76, UV-PRO ou RT-660;
2. **Legacy:** Quansheng K1 + RadioNode Box;
3. **DMR:** DM-32UV + bridge/driver experimental;
4. **LoRa:** nó Meshtastic ou SX1278 integrado ao core.

## Critérios para marcar um rádio como suportado

- conexão reproduzível;
- envio e recepção bidirecional comprovados;
- documentação de configuração;
- teste de payload RadioNode;
- comportamento de erro documentado;
- identificação/regulamentação revisadas;
- teste com ao menos duas unidades ou interoperabilidade equivalente quando aplicável.
