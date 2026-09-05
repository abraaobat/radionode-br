# Security Policy

## Project status

RadioNode BR is in early development. Interfaces, firmware and deployment procedures may change while the reference architecture is validated.

## Reporting vulnerabilities

Do not publish secrets, credentials, private station data or exploitable operational details in public issues.

For security-sensitive reports, contact the repository maintainer privately through an appropriate GitHub contact channel before public disclosure.

## Security principles

- PTT must fail safe.
- Linux/network services must not bypass radio-control protections.
- Secrets must never be committed to Git.
- Network-facing services should default to least privilege and explicit exposure.
- Debug logs must not expose credentials or sensitive configuration.
- External integrations must be treated as untrusted boundaries.

## Radio operation

Security validation does not replace regulatory compliance. Operation in RF must follow applicable licensing, station authorization, band plans and network rules.
