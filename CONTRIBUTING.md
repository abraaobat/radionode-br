# Contributing to RadioNode BR

Obrigado pelo interesse em contribuir.

O projeto ainda está em fase de fundação e validação arquitetural. Mudanças devem preservar as fronteiras de segurança e evitar acoplamento prematuro entre hardware, controle de rádio e integrações de rede.

## Fluxo

1. Abra ou relacione uma Issue quando a mudança for relevante.
2. Crie uma branch curta:
   - `feature/<tema>`
   - `fix/<tema>`
   - `docs/<tema>`
   - `refactor/<tema>`
3. Use Conventional Commits.
4. Atualize documentação e roadmap quando a mudança alterar comportamento, arquitetura ou fase.
5. Execute os testes/validações aplicáveis antes do PR.
6. Evite commits diretamente na `main` para mudanças de produto.

## Decisões arquiteturais

Mudanças difíceis de reverter devem gerar ADR, especialmente:

- protocolo ESP32 ↔ Linux;
- responsabilidade sobre PTT/COS/COR;
- mudança da arquitetura de fail-safe;
- adoção de rede/protocolo como dependência do núcleo;
- escolha de stack de firmware importante;
- mudanças de hardware de referência que alterem interfaces públicas.

## Segurança

Nunca envie para o repositório:

- senhas;
- tokens;
- chaves de API;
- dados privados de estações/usuários;
- configurações locais com segredos.

Mudanças que possam transmitir RF automaticamente devem ser testadas de forma controlada e não devem remover mecanismos de timeout/intertravamento.

## Estilo de commits

Exemplos:

```text
feat(firmware): add ptt timeout state
fix(gateway): recover serial link after reconnect
docs(architecture): define esp32 linux interface
chore(ci): add firmware validation job
```
