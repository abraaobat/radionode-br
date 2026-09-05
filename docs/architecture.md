# RadioNode BR — Arquitetura

## Objetivo

O RadioNode BR é uma plataforma modular para comunicação radioamadora e off-grid interoperável, com foco inicial no ecossistema brasileiro.

A arquitetura separa quatro domínios:

1. **core de aplicação**, independente do meio RF;
2. **transportes**, responsáveis por levar dados entre nós;
3. **drivers/adapters**, responsáveis por diferenças de rádios e interfaces físicas;
4. **gateways/serviços**, responsáveis por bridges, observabilidade e integrações externas.

## Arquitetura lógica

```text
┌─────────────────────────────────────────────────────────────┐
│ Applications / Integrations                                │
│ ATAK · Android · Web UI · APRS-IS · TAK Server · services  │
└─────────────────────────────┬───────────────────────────────┘
                              │
┌─────────────────────────────▼───────────────────────────────┐
│ RadioNode Core                                               │
│ messages · position · contacts · markers · telemetry        │
│ identity · routing policy · acknowledgements · queues        │
└─────────────────────────────┬───────────────────────────────┘
                              │ transport API
         ┌────────────────────┼────────────────────┐
         │                    │                    │
         ▼                    ▼                    ▼
┌────────────────┐   ┌────────────────┐   ┌──────────────────┐
│ VHF/UHF        │   │ DMR            │   │ LoRa/Meshtastic │
│ AX.25/KISS     │   │ Data/SMS       │   │ mesh transport   │
│ APRS/packet    │   │ experimental   │   │ low power        │
└───────┬────────┘   └───────┬────────┘   └─────────┬────────┘
        │                    │                      │
        ▼                    ▼                      ▼
 Native KISS /          DMR radio /            Meshtastic /
 Dire Wolf /            ESP32 bridge           LoRa module
 RadioNode Box
```

IP pode existir como quarto transporte opcional, principalmente para gateways, sincronização e bridges quando houver conectividade.

## Regra central

O **RadioNode Core não deve saber qual rádio está sendo usado**.

Uma mensagem, posição ou marcador deve ser representado internamente de forma comum. O transporte decide como codificar, fragmentar, transmitir, confirmar e reconstruir o conteúdo dentro das limitações de cada meio.

Exemplo:

```text
RadioNode message
      │
      ├── AX.25/KISS over VHF
      ├── DMR Data/SMS
      ├── LoRa/Meshtastic
      └── IP
```

## Transportes de primeira classe

### 1. VHF/UHF — AX.25 / KISS / APRS

Primeiro transporte a ser validado por possuir ecossistema maduro e interoperável.

Pode operar através de:

- rádio com KISS TNC Bluetooth nativo;
- Dire Wolf / DigiPi;
- TNC externo;
- futura RadioNode Box baseada em ESP32 para rádios analógicos genéricos.

Responsabilidades do transporte:

- KISS;
- AX.25;
- APRS quando aplicável;
- fragmentação/reassembly para payloads RadioNode;
- controle de acesso ao meio;
- identificação e limites regulatórios.

### 2. DMR — Data / SMS

Transporte experimental para rádios que já possuam modem DMR e GPS interno.

Objetivo:

```text
ATAK / RadioNode
       │
       ▼
 compact payload
       │
       ▼
 DMR Data/SMS
       │
       ▼
      RF
```

O Baofeng DM-32UV é candidato inicial de pesquisa. O transporte só será promovido após comprovação de acesso programático bidirecional a dados/posição em tempo real.

Não assumir equivalência entre "Digital APRS" proprietário e AX.25/APRS tradicional.

### 3. LoRa / Meshtastic

LoRa passa a ser tratado como transporte de primeira classe para baixa potência, malha e cenários sem infraestrutura VHF/DMR.

Princípios:

- não substituir conceitualmente APRS VHF;
- preservar compatibilidade com Meshtastic quando viável;
- permitir gateway controlado entre LoRa e outros transportes;
- evitar loops e retransmissão indiscriminada entre redes.

### 4. IP opcional

Usado quando Internet ou LAN estiver disponível para:

- APRS-IS;
- TAK Server;
- dashboards;
- observabilidade;
- sincronização;
- bridges explícitas.

O sistema deve continuar útil sem IP.

## Classes de hardware de rádio

### Native KISS

Rádios que já expõem TNC/KISS acessível por Bluetooth/serial e dispensam modem/áudio externo.

Candidatos iniciais:

- BTECH UV-PRO;
- VGC/Vero VR-N76;
- Radtel RT-660;
- Radioddity GA-5WB;
- móveis da mesma família, a validar.

Esses rádios devem usar drivers/adapters e compartilhar o mesmo transporte AX.25/KISS.

### DMR native modem

Rádios que já possuem modem digital e GPS, mas não necessariamente KISS.

Candidato inicial:

- Baofeng DM-32UV.

A integração deve ocorrer por driver próprio e transporte DMR, não simulando KISS se a interface real não oferecer esse contrato.

### Legacy / generic analog

Rádios sem TNC programaticamente acessível.

Exemplos iniciais:

- Quansheng K1/K5;
- HTs e móveis analógicos compatíveis com áudio/PTT.

Usam a **RadioNode Box** como adaptação física e lógica.

## RadioNode Box

A RadioNode Box deixa de ser o produto inteiro e passa a ser **um adapter de hardware para rádios legados**.

Responsabilidades possíveis:

- ESP32;
- Bluetooth/BLE;
- KISS;
- modem AFSK/AX.25;
- áudio RX/TX;
- PTT fail-safe;
- COS/COR quando disponível;
- GNSS opcional;
- alimentação e telemetria local.

O primeiro protótipo deve usar o GPS do celular sempre que isso reduzir complexidade.

## RadioNode Link

Nome provisório para bridges pequenos usados quando o rádio já contém modem/GPS, mas precisa de uma interface programática adicional.

Exemplo experimental:

```text
Android/ATAK
    │ BLE
    ▼
  ESP32
    │ serial/USB
    ▼
 DM-32UV
```

O ESP32 faria apenas bridge, framing e protocolo; não modem AFSK.

## Gateway Linux

Linux/Raspberry Pi/DigiPi é opcional, não requisito do nó portátil.

Responsabilidades possíveis:

- Dire Wolf e KISS TCP;
- APRS/APRS-IS;
- TAK bridge;
- logs e observabilidade;
- serviços de voz/rede;
- bridges entre transportes quando explicitamente habilitadas;
- configuração e operação de nós fixos.

## Segurança de RF

Quando o RadioNode controla fisicamente PTT:

1. reset, travamento ou ausência do controlador deve resultar em TX desligado;
2. watchdog e timeout máximo de TX são obrigatórios;
3. serviços externos não podem contornar proteções locais.

Quando o rádio Native KISS controla seu próprio TX, o driver deve respeitar limites, filas e política de transmissão disponíveis na API do equipamento.

## Interoperabilidade e gateways

Um gateway pode futuramente unir transportes:

```text
                  RadioNode Gateway
                  /       |       \
                VHF      DMR      LoRa
                 |        |        |
              AX.25     Data    Meshtastic
```

Bridges devem ser explícitas e policy-driven. Não é objetivo retransmitir automaticamente todo tráfego de uma rede para outra.

## TAK / CoT

ATAK/CoT é tratado como integração de aplicação, não como transporte RF.

CoT/XML bruto não deve ser presumido como payload adequado para RF de baixa taxa. O core deve permitir representação compacta de:

- posição;
- GeoChat/mensagem;
- marcadores;
- status;
- telemetria;

A integração reconstrói CoT na borda quando necessário.

## Repetidoras e infraestrutura existente

VHF/UHF e DMR podem aproveitar infraestrutura de repetidoras quando técnica, operacional e legalmente compatível. O projeto não deve assumir que qualquer repetidora de voz aceitará packet/dados.

Também devem existir cenários simplex e nós RadioNode dedicados em pontos altos.

## Hardware de referência V0.x

Não existe mais uma única pilha obrigatória. O baseline de validação passa a incluir:

- Quansheng K1/K5 + RadioNode Box experimental;
- um rádio Native KISS;
- ESP32-S3 N16R8 para bridges/controle;
- SX1278 LoRa 433 MHz como módulo experimental;
- GPS u-blox NEO-6M somente quando GPS externo for necessário;
- Raspberry Pi 3B+ com DigiPi para gateway Linux inicial.

## Interfaces

Interfaces internas devem ser explicitamente versionadas antes de se tornarem dependências estáveis:

- Core ↔ Transport;
- Transport ↔ Driver;
- RadioNode Box ↔ rádio;
- Gateway ↔ Core;
- Application integration ↔ Core.

Nenhum protocolo de mensagem RadioNode é declarado canônico neste estágio. Essa decisão exige validação e ADR próprio.

## Ecossistema relacionado

`aprsd-smsbr-plugin` continua sendo componente externo integrável. O RadioNode BR pode consumir ou documentar sua integração sem incorporar seu domínio ao núcleo.
