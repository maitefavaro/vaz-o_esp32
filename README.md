# Monitor de Vazão com ESP32 e ThingsBoard

Projeto para monitorar a vazão de um sensor conectado ao ESP32, com display LCD I2C, controle de válvula, botão para simulação de pulsos, e integração com o ThingsBoard via MQTT para visualização remota.

---

## Funcionalidades

- Leitura de pulsos do sensor (pino 18) via interrupção para cálculo da vazão.
- Display LCD I2C 16x2 para mostrar a vazão em tempo real.
- Controle de válvula (pino 27) que liga quando há fluxo.
- Botão (pino 14) que simula pulsos ao ser pressionado.
- LED (pino 2) que acende enquanto o botão estiver pressionado.
- Envio dos dados de vazão ao ThingsBoard via MQTT para monitoramento remoto.

---

## Componentes Utilizados

- ESP32 DevKit
- Sensor de fluxo (sensorPin: GPIO 18)
- Válvula (valvulaPin: GPIO 27)
- Botão (botaoPin: GPIO 14)
- LED indicador (ledPin: GPIO 2)
- Display LCD I2C 16x2 (endereçado no 0x27)

