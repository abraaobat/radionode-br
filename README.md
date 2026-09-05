# RadioNode BR

Plataforma modular e open source para comunicação radioamadora e off-grid interoperável, com foco inicial no ecossistema brasileiro.

> **Status:** bootstrap / `0.1.0-alpha.0`. A arquitetura, interfaces, transportes e hardware de referência ainda estão em validação.

## Visão

O RadioNode BR passa a ser tratado como uma **plataforma multimodo**, na qual aplicações e serviços usam um núcleo comum e os meios de RF entram como transportes substituíveis.

Transportes de primeira classe planejados:

- **VHF/UHF analógico + AX.25/KISS/APRS**;
- **DMR Data/SMS**, quando houver acesso programático seguro ao rádio;
- **LoRa / Meshtastic** para malha de baixa potência;
- **IP** como transporte opcional quando houver rede disponível.

Acima desses transportes, o mesmo núcleo deve poder oferecer mensagens, posição, contatos, marcadores, telemetria e integração futura com TAK/CoT.

```text
                         RadioNode Core
                 messages · position · routing
                    contacts · telemetry
                              │
             ┌────────────────┼────────────────┐
             │                │                │
             ▼                ▼                ▼
        VHF/UHF AX.25        DMR          LoRa/Meshtastic
          KISS / APRS      Data/SMS             mesh
             │                │                │
             └────────────────┼────────────────┘
                              │
                     ATAK / Android / Web
```

## Classes de rádio

O projeto não deve depender de um único modelo de transceptor.

1. **Native KISS radios** — rádios que já expõem TNC/KISS e podem dispensar hardware RadioNode externo. Candidatos: BTECH UV-PRO, VGC/Vero VR-N76, Radtel RT-660, Radioddity GA-5WB e móveis compatíveis.
2. **DMR radios** — rádios com modem DMR/GPS próprio. O Baofeng DM-32UV é candidato experimental para um transporte `dmr` específico.
3. **Legacy/generic radios** — rádios analógicos sem TNC acessível, como Quansheng K1/K5 e outros HTs/móveis. Esses usam a futura **RadioNode Box** para áudio, PTT, KISS/AX.25 e conectividade local.

Consulte [Matriz de hardware](docs/hardware-matrix.md).

## Arquitetura física

A arquitetura continua separando funções críticas de RF das funções de rede e serviços:

- **ESP32 / RadioNode Box**: quando necessário, controle determinístico, PTT, temporização, proteções, áudio/modem, telemetria e conectividade local;
- **rádio Native KISS**: pode substituir parte ou toda a RadioNode Box;
- **Linux / Raspberry Pi / DigiPi**: gateway opcional para Dire Wolf, APRS-IS, serviços, logs, dashboard e bridges;
- **LoRa/Meshtastic**: transporte independente, não substituto de VHF/APRS.

## Hardware de referência V0.x

O hardware deixa de ser uma única configuração obrigatória. As plataformas iniciais de validação serão:

- Quansheng K1/K5 + RadioNode Box experimental;
- pelo menos um rádio Native KISS;
- ESP32-S3 N16R8 para protótipos de controle/bridge;
- SX1278 LoRa 433 MHz como módulo experimental;
- GPS u-blox NEO-6M quando GPS externo for necessário;
- Raspberry Pi 3B+ com DigiPi para gateway Linux inicial.

## Princípios

1. **Transport-agnostic core**: aplicação e mensagem não devem depender do meio RF.
2. **PTT fail-safe**: quando o RadioNode controla PTT, reset, travamento ou ausência do controlador deve resultar em TX desligado.
3. **Drivers por rádio, não forks por produto**: diferenças de hardware entram em adapters/drivers.
4. **VHF, DMR e LoRa são transportes distintos**: nenhum deve ser tratado como substituto universal dos demais.
5. **Interoperabilidade primeiro**: Native KISS, DMR, Dire Wolf/DigiPi e RadioNode Box devem convergir para interfaces comuns.
6. **DigiPi suportado, não obrigatório**.
7. **Hardware validado antes da PCB própria**.
8. **Conformidade regulatória por transporte**: operação em RF deve respeitar regras brasileiras, identificação, frequências e limitações aplicáveis.

## Documentação

- [Arquitetura](docs/architecture.md)
- [Roadmap](docs/roadmap.md)
- [Matriz de hardware](docs/hardware-matrix.md)
- [ADR-0001 — fronteiras entre controle de rádio e serviços de rede](docs/decisions/ADR-0001-system-boundaries.md)
- [ADR-0002 — arquitetura multimodo e transportes de primeira classe](docs/decisions/ADR-0002-multitransport-core.md)
- [Política de segurança](SECURITY.md)
- [Como contribuir](CONTRIBUTING.md)
- [Changelog](CHANGELOG.md)

## Governança

O projeto usa:

- Git como histórico oficial;
- branches curtas (`feature/`, `fix/`, `docs/`, `refactor/`);
- Conventional Commits;
- Semantic Versioning;
- ADRs para decisões estruturais;
- CI para validar o baseline do repositório;
- documentação e roadmap sincronizados com mudanças relevantes.

A versão canônica está no arquivo [`VERSION`](VERSION).

## Ecossistema relacionado

- [`aprsd-smsbr-plugin`](https://github.com/abraaobat/aprsd-smsbr-plugin): integração APRS/APRSD com SMS brasileiro, tratada como componente externo integrável ao RadioNode BR.

## Licença

Apache License 2.0. Consulte [`LICENSE`](LICENSE).

## Aviso operacional

O RadioNode BR é um projeto experimental de radioamadorismo. Operação em RF deve respeitar a regulamentação aplicável, o licenciamento da estação, as regras do serviço utilizado e as políticas de repetidoras/redes integradas.
