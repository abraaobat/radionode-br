# RadioNode BR — Accessibility Engine

## Objetivo

O RadioNode BR deve oferecer operação útil sem depender de tela, com prioridade inicial para operadores cegos ou com baixa visão.

A acessibilidade é tratada como uma **camada transversal** do sistema, não como um transporte RF, modem ou dependência do RadioNode Core. Ela consome eventos semânticos do core, drivers e telemetria local e os transforma em feedback acessível.

Referência arquitetural inicial:

- [`jewelux/talking-swr-meter-LX1WJ`](https://github.com/jewelux/talking-swr-meter-LX1WJ) — ESP32-S3, fala por I2S, Morse, feedback tonal e operação sem display.

A adoção é de conceitos e padrões. O código upstream não deve ser copiado ou incorporado automaticamente ao firmware Apache-2.0 do RadioNode BR; o firmware do projeto de referência é GPL-3.0 e sua documentação é CC BY-SA 4.0.

## Princípios

1. **Screenless-first:** funções essenciais devem poder ser operadas sem leitura visual.
2. **Feedback redundante:** quando possível, eventos importantes devem ter mais de uma modalidade — fala, Morse, tons, vibração no host ou acessibilidade nativa do aplicativo.
3. **Não bloquear RF nem segurança:** fala, Morse ou TTS nunca podem atrasar watchdog, timeout de TX, de-key do PTT, RX/TX ou processamento crítico.
4. **Eventos semânticos:** o Accessibility Engine recebe eventos como `ptt_fault`, `gps_acquired` ou `aprs_message_received`; ele não deve interpretar diretamente protocolos RF para decidir o que falar.
5. **Prioridade e interrupção:** alertas críticos interrompem feedback informativo; mensagens repetitivas devem ser limitadas para evitar sobrecarga auditiva.
6. **Operação local:** recursos essenciais devem funcionar sem Internet.
7. **Português brasileiro:** `pt-BR` é o perfil de voz/mensagens inicial, sem impedir outros idiomas no futuro.
8. **Hardware opcional:** o nó continua funcional sem alto-falante/buzzer local; acessibilidade também pode ser oferecida pelo RadioLink Mobile ou outro host.

## Arquitetura

```text
Radio / RF / sensors / drivers
            │
            ▼
┌───────────────────────────────┐
│ RadioNode Core + telemetry    │
│ messages · position · status │
│ PTT safety · connection      │
└───────────────┬───────────────┘
                │ semantic events
                ▼
┌───────────────────────────────┐
│ RadioNode Accessibility      │
│ Engine                        │
│                               │
│ event mapping                 │
│ priority queue                │
│ rate limiting                 │
│ localization                  │
│ modality policy               │
└───────┬────────┬────────┬─────┘
        │        │        │
        ▼        ▼        ▼
     Speech    Morse     tones
      I2S      buzzer    buzzer/I2S
        │
        └───────────────┐
                        ▼
                 host/mobile accessibility
                 screen reader · haptics
```

## Contrato de eventos

O formato canônico ainda será definido em F1. A camada de acessibilidade deve consumir um contrato pequeno e independente da origem do evento.

Exemplo conceitual:

```text
AccessibilityEvent
  kind: ptt_fault | gps_acquired | message_rx | battery_low | ...
  priority: critical | operational | informational
  source: core | transport | driver | hardware
  params: structured values
  timestamp
  repeat_policy
```

O evento deve carregar valores estruturados. A formação da frase fica na camada de localização/acessibilidade.

Exemplo:

```text
kind = frequency_changed
params = { hz: 146950000 }
```

pode produzir em `pt-BR`:

```text
"Frequência cento e quarenta e seis ponto novecentos e cinquenta megahertz."
```

sem obrigar o core a armazenar a frase pronta.

## Modalidades

### 1. Fala local

Baseline de hardware recomendado para protótipo:

- ESP32-S3;
- amplificador I2S MAX98357A ou equivalente;
- pequeno alto-falante;
- volume configurável.

A implementação inicial pode usar vocabulário/dicionário de áudio limitado ou outro mecanismo offline adequado. TTS de vocabulário livre não é requisito para o primeiro MVP.

### 2. Morse

Morse é uma saída complementar simples, determinística e de baixo custo.

Pode ser usado para:

- indicativo;
- estado curto;
- confirmação de operação;
- códigos de erro;
- valores selecionados quando adequado.

### 3. Feedback tonal

Tons são apropriados para informação contínua ou relativa, onde fala repetitiva seria lenta ou cansativa.

Exemplos:

- qualidade/tendência de sinal;
- busca de mínimo/máximo durante ajuste;
- confirmação curta;
- alerta de erro;
- estado conectado/desconectado.

O padrão do Talking SWR Meter de usar pitch contínuo para auxiliar ajuste é referência de interação, não uma exigência de que o RadioNode possua medidor de SWR.

### 4. Host / RadioLink Mobile

Quando conectado a um smartphone ou computador, o mesmo fluxo de eventos pode ser exposto para:

- VoiceOver/TalkBack;
- fala do sistema;
- vibração/haptics;
- notificações acessíveis;
- atalhos e controles com labels semânticos.

O hardware local e o host podem coexistir.

## Catálogo inicial de eventos

### Críticos

- `ptt_timeout`;
- `ptt_fault_latched`;
- `hardware_fault`;
- `battery_critical`;
- `overtemperature`, quando houver sensor;
- falha de armazenamento/configuração crítica.

### Operacionais

- boot concluído;
- modo operacional alterado;
- rádio/transport conectado ou desconectado;
- frequência/canal alterado quando disponível;
- GPS adquirido/perdido;
- TX iniciado/finalizado quando útil;
- beacon transmitido;
- mensagem APRS/RadioNode recebida;
- acknowledgement recebido;
- KISS host conectado/desconectado.

### Informativos

- bateria;
- posição disponível;
- indicativo/perfil ativo;
- número de mensagens pendentes;
- status de rede/gateway;
- versão de firmware.

Leituras de SWR/potência só entram no catálogo se o hardware correspondente existir. Elas não fazem parte do baseline obrigatório da RadioNode Box.

## Prioridades

Sugestão inicial:

```text
critical       → interrompe fala/tom informativo
operational    → fila curta, descartável quando obsoleto
informational  → sob demanda ou rate-limited
continuous     → preferir tons em vez de fala repetitiva
```

O de-key físico do PTT e demais mecanismos de segurança permanecem fora dessa fila e têm precedência absoluta.

## Controles físicos

O primeiro protótipo acessível pode usar poucos botões com funções previsíveis:

- repetir último estado;
- anunciar modo/conexão;
- anunciar bateria;
- cancelar fala;
- alternar volume/modo de feedback.

Uma ladder resistiva em ADC, como no projeto LX1WJ, é uma opção de referência, não uma decisão de hardware ainda.

## Critérios de validação

A camada só deve ser promovida a funcional quando demonstrar:

- operação sem display para tarefas definidas;
- fala/Morse sem bloquear processamento crítico;
- alerta de `ptt_fault` sem interferir no de-key físico;
- comportamento determinístico sob fila de muitos eventos;
- rate limiting de eventos repetitivos;
- funcionamento offline dos alertas essenciais;
- labels e fluxo compatíveis com leitor de tela no host quando essa integração existir;
- teste prático com roteiro eyes-free e, idealmente, avaliação de usuário com deficiência visual.

## Fora do escopo inicial

- reconhecimento de voz obrigatório;
- TTS em nuvem;
- assistente conversacional embarcado;
- medidor de SWR integrado como requisito da RadioNode Box;
- substituição dos mecanismos de segurança por avisos sonoros;
- dependência de Internet para feedback essencial.

## Referências

- Talking SWR Meter LX1WJ: <https://github.com/jewelux/talking-swr-meter-LX1WJ>
- ADR correspondente: [`decisions/ADR-0004-accessibility-engine.md`](decisions/ADR-0004-accessibility-engine.md)
- Arquitetura geral: [`architecture.md`](architecture.md)
- Roadmap: [`roadmap.md`](roadmap.md)
