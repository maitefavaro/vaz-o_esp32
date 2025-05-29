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

--



## Configuração do Projeto

### Biblioteca necessárias

- [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
- WiFi (nativa ESP32)
- PubSubClient (para MQTT)

### Configurações do Wi-Fi

No código, configure seu Wi-Fi:

```cpp
const char* ssid = "SEU_SSID";
const char* password = "SUA_SENHA";
Configurações do ThingsBoard
Crie um dispositivo no ThingsBoard.

Copie o Access Token do dispositivo.

Cole no código em:

cpp
Copiar
Editar
const char* access_token = "SEU_TOKEN_AQUI";
Como usar
Conecte o ESP32 ao seu computador.

Ajuste as configurações Wi-Fi e ThingsBoard no código.

Faça o upload do código para o ESP32.

Abra o monitor serial para acompanhar mensagens de debug.

Acesse seu dispositivo no ThingsBoard e visualize os dados na aba Latest Telemetry.

Configure um dashboard no ThingsBoard para mostrar os dados de vazão.

Estrutura do Código
contarPulso() — função de interrupção para contar pulsos do sensor.

setupWiFi() — conecta o ESP32 à rede Wi-Fi.

reconnect() — mantém a conexão MQTT com o ThingsBoard.

loop() — lê o botão, atualiza o LCD, controla a válvula e publica a telemetria.
