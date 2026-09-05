# RadioNode BR — Roadmap

Este roadmap organiza a evolução do projeto como uma plataforma multimodo, sem amarrar o núcleo a um único rádio, protocolo ou rede.

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

## F4 — RadioNode Box / legacy radio adapter

Objetivo: permitir que rádios analógicos sem TNC participem do mesmo ecossistema.

- Quansheng K1/K5 como plataforma inicial de bancada
- ESP32 para bridge local
- interface de áudio RX/TX
- PTT fail-safe
- timeout máximo de TX
- modem AFSK 1200
- AX.25/KISS
- Bluetooth/BLE
- GPS do celular como baseline
- GNSS externo opcional
- protótipo sem PCB própria
- definir conectores/cabos substituíveis por família de rádio
- somente depois avaliar PCB e enclosure próprios

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

## F14 — Reference hardware

- consolidar RadioNode Box validada
- definir diagrama elétrico
- revisar alimentação e proteção
- revisar áudio/PTT/COS/COR
- revisar conectores e manutenção
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

## Regra de promoção de fase

Uma fase só é considerada concluída quando os artefatos aplicáveis estiverem documentados, testados e registrados no Git. Hardware, compatibilidade de rádio ou comportamento de RF não deve ser marcado como validado apenas por documentação do fabricante ou implementação de software.
