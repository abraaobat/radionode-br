# Changelog

Todas as mudanças relevantes do RadioNode BR serão registradas neste arquivo.

O projeto segue [Semantic Versioning](https://semver.org/) a partir das versões publicadas.

## [Unreleased]

### Added

- Estrutura inicial de governança do repositório.
- Documentação canônica de arquitetura, roadmap e decisões.
- Baseline de contribuição, segurança e CI.
- Arquitetura multimodo com VHF/UHF AX.25/KISS, DMR Data/SMS e LoRa/Meshtastic como transportes de primeira classe.
- Separação explícita entre RadioNode Core, transports, drivers/adapters e integrações.
- Classes de rádio `Native KISS`, `DMR native modem` e `Legacy/generic analog`.
- Conceitos de RadioNode Box, RadioNode Link, RadioNode Mobile e RadioNode Gateway.
- ADR-0002 para a decisão de arquitetura transport-agnostic.
- Matriz inicial de hardware candidato e critérios para promoção a suporte oficial.
- Fases específicas de roadmap para Native KISS, DMR, LoRa/Meshtastic, TAK/CoT e gateways multi-transport.

## [0.1.0-alpha.0] - 2026-09-04

### Added

- Inicialização do repositório RadioNode BR.
- Definição da visão modular ESP32 + Linux/Raspberry Pi/DigiPi.
- Hardware de referência V0.1 e princípios de segurança de PTT.
