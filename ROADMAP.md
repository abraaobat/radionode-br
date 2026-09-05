# RadioNode BR — Roadmap

## V0.1 — Núcleo embarcado
- ESP32-S3 N16R8 inicializado
- Wi-Fi e configuração persistente
- watchdog
- display ST7789
- GPS NEO-6M
- SX1278 LoRa 433 MHz
- status local e telemetria básica

## V0.2 — Link ESP32 ↔ Linux
- protocolo de controle e telemetria via USB/serial
- comandos de status
- eventos RX/TX
- política de autorização de TX
- fallback de manutenção via Wi-Fi

## V0.3 — COS/PTT em bancada
- entrada COS/COR simulada
- saída PTT simulada por LED/carga
- anti-kerchunk
- hang/hold time
- TOT
- calm-down
- boot inhibit

## V0.4 — Interface real de rádio
- isolamento elétrico
- PTT fail-safe
- adaptação COS/COR
- interface de áudio
- testes com rádios RX/TX reais

## V0.5 — Telemetria e proteções
- tensão
- corrente
- temperatura
- alarmes
- watchdog de hardware quando aplicável
- eventos e logs

## V0.6 — APRS
- rádio VHF dedicado
- Direwolf
- APRS-IS
- perfil iGate
- perfil digipeater
- beacon/telemetria
- integração opcional com aprsd-smsbr-plugin

## V0.7 — Repetidora conectada
- SvxLink
- EchoLink
- integração de áudio
- integração com autoridade PTT do ESP32

## V0.8 — PCB própria
- esquemático consolidado
- BOM
- layout PCB
- conectores de rádio
- proteção e alimentação
- revisão de EMC/RF

## V0.9 — Nó piloto
- gabinete
- instalação de campo
- testes de estabilidade
- métricas
- documentação de instalação e operação

## V1.0 — RadioNode BR operacional
- firmware estável
- gateway Linux instalável
- documentação completa
- hardware de referência reproduzível
- integração APRS e EchoLink validada

## V2.x — Voz digital / redes adicionais
- MMDVM
- DMR / BrandMeister
- XLX
- YSF/C4FM
- outros adaptadores de rede quando tecnicamente e operacionalmente justificáveis
