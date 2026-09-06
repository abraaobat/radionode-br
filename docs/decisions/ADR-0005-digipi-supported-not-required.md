# ADR-0005 — DigiPi supported, not required

- Status: Accepted
- Date: 2026-09-04

## Context

O protótipo inicial usa Raspberry Pi 3B+ com DigiPi, mas amarrar o gateway a uma única imagem Linux reduziria portabilidade e adoção.

## Decision

DigiPi será uma plataforma oficialmente suportada, mas o gateway deverá permanecer instalável em Raspberry Pi OS/Debian compatível.

## Consequences

- Integrações com DigiPi ficam isoladas da lógica principal.
- Scripts e serviços devem evitar dependências desnecessárias da imagem.
- Outras SBCs Linux poderão ser suportadas no futuro.
