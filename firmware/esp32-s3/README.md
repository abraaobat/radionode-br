# ESP32-S3 Firmware

Firmware do controlador embarcado do RadioNode BR.

Escopo inicial:
- boot seguro;
- configuração persistente;
- watchdog;
- interface USB/serial com Linux;
- display ST7789;
- GPS NEO-6M;
- SX1278 LoRa;
- COS/COR e PTT em fases posteriores;
- telemetria e proteções locais.

Nenhum GPIO definitivo será congelado antes da identificação exata da placa ESP32-S3 N16R8 usada no protótipo.
