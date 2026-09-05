# RadioNode BR — Roadmap

Este roadmap organiza a evolução do projeto sem antecipar decisões de hardware, protocolo ou rede que ainda precisam de validação prática.

## F0 — Foundation 🟡

- [x] criar repositório público
- [x] definir visão inicial e princípios de segurança
- [x] registrar hardware de referência V0.1
- [x] criar arquitetura canônica
- [x] criar roadmap e ADR inicial
- [x] adicionar versionamento e changelog
- [x] definir licença open source do projeto (Apache-2.0)
- [ ] configurar About/topics do GitHub

## F1 — Core interfaces and bench plan

- definir estados do nó e máquina de estados principal
- definir interface ESP32 ↔ Linux
- definir comandos, eventos, telemetria e códigos de falha
- definir watchdog e comportamento de desconexão
- criar plano de testes de bancada
- registrar decisões de protocolo em ADR

## F2 — ESP32 radio-control core

- leitura confiável de COS/COR
- controle fail-safe de PTT
- timeout máximo de transmissão
- intertravamentos e estados de falha
- watchdog
- logs/telemetria local mínima
- testes automatizáveis onde aplicável
- validação de bancada antes de integrar redes

## F3 — Local peripherals and telemetry

- integrar GPS u-blox NEO-6M
- integrar display ST7789 240x240
- definir telemetria local
- validar SX1278 LoRa como módulo opcional e separado de APRS
- definir persistência/configuração local necessária

## F4 — Linux gateway baseline

- validar Raspberry Pi 3B+ + DigiPi como gateway inicial
- documentar instalação reproduzível
- definir serviço de comunicação com ESP32
- logs estruturados e health checks
- preparar compatibilidade com Raspberry Pi OS/Debian sem DigiPi

## F5 — APRS integration

- integrar Dire Wolf/KISS
- validar APRS VHF
- validar APRS-IS quando Internet estiver disponível
- telemetria/beacons conforme regras aplicáveis
- documentar callsign/path/configuração
- avaliar integração opcional com `aprsd-smsbr-plugin`

## F6 — Network adapters

Integrações entram como módulos independentes, conforme necessidade e validação:

- EchoLink / SvxLink
- BrandMeister
- XLX
- YSF
- outras redes compatíveis

Nenhuma dessas redes deve se tornar dependência obrigatória do núcleo.

## F7 — Reference hardware

- consolidar diagrama elétrico da versão validada em bancada
- definir interfaces de áudio/PTT/COS/COR
- revisar alimentação e proteção
- revisar conectores e manutenção
- somente então avaliar PCB própria

## F8 — Field validation

- testes prolongados em bancada
- testes de falha de energia/reboot/desconexão
- testes de PTT travado e timeouts
- testes térmicos e de alimentação quando aplicável
- operação controlada em RF respeitando regulamentação e licenciamento
- documentar problemas conhecidos e recuperação

## F9 — Public release readiness

- guia de montagem
- guia de instalação e configuração
- matriz de compatibilidade
- exemplos de configuração
- documentação de segurança e limitações
- CI adequado ao firmware/software existente
- releases versionadas
- critérios para `v1.0.0`

## Regra de promoção de fase

Uma fase só é considerada concluída quando os artefatos aplicáveis estiverem documentados, testados e registrados no Git. Hardware ou comportamento de RF não deve ser marcado como validado apenas por implementação de software.
