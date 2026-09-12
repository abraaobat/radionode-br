# RadioNode BR — Roadmap

Este roadmap organiza a evolução do projeto como uma plataforma multimodo, sem amarrar o núcleo a um único rádio, protocolo ou rede.

## Estado atual — 2026-09-12

O núcleo AFSK candidato (`dkaukov/esp32-afsk`) já passa testes nativos upstream e build ESP32-S3 no CI. A camada lógica de segurança de PTT também está implementada e testada: timeout máximo de TX, fault latch, limpeza explícita e tratamento de wraparound de `millis()`. O próximo gate continua sendo físico: áudio RX/TX + PTT GPIO + AFSK real em bancada antes de promover o RadioNode Box como validado.

Em paralelo, acessibilidade passa a ser uma capacidade transversal de primeira classe. O `jewelux/talking-swr-meter-LX1WJ` foi adotado como referência arquitetural para operação screenless com fala, Morse e feedback tonal. O desenho está registrado em `docs/accessibility.md` e no ADR-0004. Essa trilha não altera nem bloqueia o gate físico de F4.

## F0 — Foundation 🟡

- [x] criar repositório público
- [x] definir visão inicial e princípios de segurança
- [x] registrar hardware de referência V0.1
- [x] criar arquitetura canônica
- [x] criar roadmap e ADR inicial
- [x] adicionar versionamento e changelog
- [x] definir licença open source do projeto (Apache-2.0)
- [x] adotar arquitetura multimodo com VHF/AX.25, DMR e LoRa/Meshtastic como transportes de primeira classe
- [x] separar RadioNode Core, transports, drivers e hardware adapters
- [x] definir acessibilidade como capacidade transversal e registrar ADR específico
- [ ] configurar About/topics do GitHub

## F1 — Core contracts and message model

- definir modelo comum de identidade do nó
- definir mensagens, posição, contatos, marcadores, status e telemetria
- definir envelope RadioNode independente do transporte
- definir acknowledgements, retries, TTL e deduplicação
- definir política de filas/prioridades
- definir interface `Core ↔ Transport`
- definir interface `Transport ↔ Driver`
- definir versionamento dos contratos
- definir contrato de eventos semânticos consumível pelo Accessibility Engine
- registrar formato canônico em ADR após testes

## F2 — VHF/UHF AX.25/KISS baseline

Objetivo: primeiro transporte funcional e interoperável.

- validar KISS como interface do transporte VHF/UHF
- validar AX.25 packet
- validar APRS tradicional
- criar adapter Dire Wolf/KISS TCP
- criar driver para pelo menos um rádio Native KISS
- testar simplex entre dois nós
- validar mensagens e posição RadioNode sobre payload compacto
- definir limites de tamanho/fragmentação
- documentar callsign e identificação
- testar comportamento através de infraestrutura compatível quando autorizado

## F3 — Native KISS radio support

- validar BTECH UV-PRO como benchmark de interoperabilidade
- avaliar VGC/Vero VR-N76 como plataforma aberta principal
- validar Radtel RT-660 como opção de baixo custo
- avaliar Radioddity GA-5WB
- mapear protocolo/família compartilhada quando aplicável
- criar matriz de recursos por modelo
- evitar código duplicado através de driver comum quando possível
- validar Bluetooth SPP/BLE conforme cada rádio
- testar interoperabilidade RF entre marcas/modelos

## F4 — RadioNode Box / legacy radio adapter 🟡

Objetivo: permitir que rádios analógicos sem TNC participem do mesmo ecossistema.

- [x] Quansheng K1/K5 definido como plataforma inicial de bancada
- [x] ESP32-S3 definido como bridge local do MVP
- [ ] interface física de áudio RX/TX validada
- [x] PTT fail-safe implementado e validado em software
- [x] timeout máximo de TX implementado e validado em software
- [x] `dkaukov/esp32-afsk` adotado e fixado como candidato principal do núcleo AFSK
- [x] testes nativos upstream do AFSK passam no CI
- [x] candidato AFSK compila para ESP32-S3 no CI
- [ ] RX AFSK 1200 real validado em bancada
- [ ] TX AFSK 1200 real validado em bancada
- [ ] PTT GPIO físico validado com fail-safe e timeout
- [ ] AX.25/KISS integrado ao firmware do RadioNode Box
- [ ] Bluetooth/BLE KISS
- [x] GPS do celular definido como baseline
- [ ] GNSS externo opcional
- [ ] protótipo sem PCB própria montado e validado
- [ ] definir conectores/cabos substituíveis por família de rádio
- [ ] revisar disponibilidade de I2S/GPIO para perfil acessível opcional sem comprometer áudio/PTT
- [ ] somente depois avaliar PCB e enclosure próprios

**Gate de promoção de F4:** software/CI não substitui bancada. F4 só avança para validação funcional após prova documentada de RX + TX AFSK e desacionamento físico seguro do PTT.

## A11Y — Accessibility Engine / operação screenless 🟡

Trilha transversal. Pode evoluir em paralelo às fases principais e não bloqueia a validação física de F4.

- [x] adotar `jewelux/talking-swr-meter-LX1WJ` como referência arquitetural de acessibilidade
- [x] documentar fronteira de licença: referência de padrões sem incorporação automática do código GPL-3.0
- [x] definir Accessibility Engine separado de transport/modem/RF
- [x] documentar fala, Morse, tons e acessibilidade no host como modalidades complementares
- [x] definir `pt-BR` como perfil inicial de localização
- [x] estabelecer princípio screenless-first para funções essenciais selecionadas
- [ ] fechar contrato `AccessibilityEvent` após F1 definir o modelo comum de eventos
- [ ] implementar prioridade `critical / operational / informational`
- [ ] implementar cancelamento, interrupção, deduplicação e rate limiting
- [ ] criar vocabulário offline `pt-BR` inicial
- [ ] prototipar saída I2S com MAX98357A ou equivalente
- [ ] prototipar Morse/buzzer
- [ ] validar feedback tonal para eventos contínuos apropriados
- [ ] expor os mesmos eventos ao RadioLink Mobile para VoiceOver/TalkBack e haptics
- [ ] criar controles físicos mínimos: repetir status, cancelar fala e volume/modo de feedback
- [ ] validar que áudio acessível não interfere em AFSK, watchdog, PTT fail-safe ou timeout de TX
- [ ] executar roteiro de operação eyes-free
- [ ] realizar, quando possível, avaliação com operador cego ou com baixa visão

**Critério de promoção da trilha A11Y:** acessibilidade deve ser validada por tarefas executáveis sem display e sem degradação dos caminhos críticos de RF/segurança; existência de TTS ou buzzer no código, isoladamente, não conta como validação funcional.

## F5 — LoRa / Meshtastic transport

- validar SX1278/LoRa como transporte independente
- estudar integração por API/protocolo Meshtastic
- definir mapeamento do envelope RadioNode para payload LoRa
- respeitar limites de duty cycle, payload e regulamentação
- implementar TTL/deduplicação adequados a mesh
- validar mensagens e posição
- testar operação sem Internet
- estudar gateway controlado LoRa ↔ VHF
- prevenir loops entre transports

## F6 — DMR transport research

Objetivo: explorar rádios com modem digital/GPS interno sem fingir equivalência com AX.25/KISS.

- usar Baofeng DM-32UV como primeiro candidato experimental
- documentar protocolo serial/USB disponível
- verificar acesso em tempo real a GPS
- verificar envio programático de DMR SMS/Data
- verificar recepção programática de DMR SMS/Data
- validar operação DMR simplex sem Internet
- desenhar `RadioNode-DMR` compact payload
- avaliar ESP32 como `RadioNode Link`
- testar mensagens, posição e status
- somente promover DMR a transporte estável após bidirecionalidade comprovada

## F7 — TAK / CoT integration

- definir adapter de aplicação ATAK/CoT
- não transmitir CoT/XML bruto quando inadequado ao RF
- criar representação compacta para posição
- criar representação compacta para GeoChat/mensagens
- criar representação compacta para marcadores
- reconstruir CoT na borda
- validar com Native KISS primeiro
- avaliar plugin ATAK próprio
- estudar compatibilidade/interoperabilidade com ecossistemas TAK existentes

## F8 — Linux gateway baseline

- validar Raspberry Pi 3B+ + DigiPi como gateway inicial
- documentar instalação reproduzível
- Dire Wolf/KISS TCP
- logs estruturados e health checks
- preparar compatibilidade com Raspberry Pi OS/Debian sem DigiPi
- bridge controlada entre transports
- configuração e observabilidade
- operação sem dependência obrigatória de Internet

## F9 — Network and server adapters

Integrações externas entram como módulos independentes:

- APRS-IS
- TAK Server
- EchoLink / SvxLink
- BrandMeister, quando aplicável
- XLX
- YSF
- `aprsd-smsbr-plugin`
- outras redes compatíveis

Nenhuma rede externa deve se tornar dependência obrigatória do core.

## F10 — RadioNode Gateway

Objetivo: nó fixo capaz de interligar transportes de forma explícita e controlada.

- VHF/AX.25 interface
- DMR interface, se F6 for validada
- LoRa/Meshtastic interface
- IP opcional
- políticas de bridge
- filtros por tipo de mensagem
- prevenção de loops
- observabilidade
- operação em ponto alto
- avaliar integração autorizada com infraestrutura de repetidoras

## F11 — Mobile / 25–50 W profile

- avaliar rádios móveis Native KISS
- candidatos iniciais: Radioddity DB50-B, Vero/VGC VR-N7600 e equivalentes
- validar alimentação automotiva
- proteção contra ruído/transientes
- GPS/posição móvel
- PTT e limites térmicos
- perfil veicular para gateway/nó de campo

## F12 — Security and regulatory profiles

- perfil `HAM-BR`
- identificação por indicativo quando exigida
- frequências e parâmetros documentados por transporte
- criptografia de conteúdo desabilitada em perfis de radioamador quando incompatível com a regulamentação
- política explícita para bridges e repetidoras
- limites de transmissão/timeout
- documentação de responsabilidades do operador

## F13 — Field validation

- testes prolongados em bancada
- testes simplex
- testes multi-transport
- testes de falha de energia/reboot/desconexão
- testes de PTT travado e timeouts
- testes térmicos e de alimentação
- testes de alcance com metodologia documentada
- testes de interoperabilidade entre modelos de rádio
- operação controlada em RF respeitando regulamentação e licenciamento
- documentar problemas conhecidos e recuperação
- incluir cenários eyes-free aplicáveis ao perfil acessível

## F14 — Reference hardware

- consolidar RadioNode Box validada
- definir diagrama elétrico
- revisar alimentação e proteção
- revisar áudio/PTT/COS/COR
- revisar conectores e manutenção
- definir variante/perfil acessível opcional com I2S/alto-falante/buzzer após validação de recursos
- avaliar RadioNode Link para DMR
- avaliar RadioNode Gateway hardware profile
- somente então avaliar PCB própria por produto

## F15 — Public release readiness

- guia de montagem
- guia de instalação e configuração
- matriz de compatibilidade
- documentação por transport
- exemplos de configuração
- documentação de segurança e limitações
- guia de acessibilidade e operação sem tela para perfis suportados
- CI adequado ao firmware/software existente
- releases versionadas
- critérios para `v1.0.0`

## Matriz de plataformas prioritárias

| Plataforma | Papel no projeto |
|---|---|
| VGC/Vero VR-N76 | Native KISS / plataforma aberta |
| BTECH UV-PRO | benchmark ATAK/KISS |
| Radtel RT-660 | Native KISS de baixo custo |
| Radioddity GA-5WB | interoperabilidade da família |
| Baofeng DM-32UV | pesquisa RadioNode-DMR |
| Quansheng K1/K5 | RadioNode Box / rádio legado |
| DigiPi + Dire Wolf | gateway KISS/Linux |
| Meshtastic/LoRa | transporte mesh de baixa potência |

## Referências arquiteturais selecionadas

| Referência | Uso no RadioNode BR |
|---|---|
| `dkaukov/esp32-afsk` | candidato principal do modem AFSK 1200 do MVP, sujeito ao gate físico e à fronteira GPL |
| `jewelux/talking-swr-meter-LX1WJ` | referência de interação acessível screenless: fala, Morse, feedback tonal e controles físicos |

## Regra de promoção de fase

Uma fase só é considerada concluída quando os artefatos aplicáveis estiverem documentados, testados e registrados no Git. Hardware, compatibilidade de rádio, acessibilidade ou comportamento de RF não deve ser marcado como validado apenas por documentação do fabricante, existência de código ou implementação de software.