#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <PubSubClient.h>

// --- PINOS ---
const int sensorPin = 18;
const int valvulaPin = 27;
const int botaoPin = 14; // Pino do botão
const int ledPin = 2;    // LED vai piscar quando botão pressionado

// --- WIFI ---
const char* ssid = "Wokwi-GUEST"; // ou sua rede real
const char* password = "";

// --- MQTT (ThingsBoard) ---
const char* mqtt_server = "mqtt.thingsboard.cloud";
const int mqtt_port = 1883;
const char* access_token = "MEg73gMMl4xkry9nc52N"; // Cole aqui o token do dispositivo

WiFiClient espClient;
PubSubClient client(espClient);

// --- VARIÁVEIS ---
volatile int pulsos = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- FUNÇÃO DE INTERRUPÇÃO ---
void IRAM_ATTR contarPulso() {
  pulsos++;
}

// --- WIFI ---
void setupWiFi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando-se ao Wi-Fi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado ao Wi-Fi");
}

// --- MQTT ---
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao ThingsBoard...");
    if (client.connect("ESP32Client", access_token, NULL)) {
      Serial.println("conectado!");
    } else {
      Serial.print("falhou. rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5s");
      delay(5000);
    }
  }
}

void setup() {
  Wire.begin(21, 22);

  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(valvulaPin, OUTPUT);
  pinMode(botaoPin, INPUT_PULLUP); // Botão como entrada
  pinMode(ledPin, OUTPUT);         // LED como saída

  digitalWrite(valvulaPin, LOW);
  digitalWrite(ledPin, LOW);       // LED apagado inicialmente

  attachInterrupt(digitalPinToInterrupt(sensorPin), contarPulso, RISING);

  Serial.begin(115200);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Monitorando...");

  setupWiFi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // LED pisca quando botão for pressionado
  if (digitalRead(botaoPin) == LOW) { // Botão pressionado
    digitalWrite(ledPin, HIGH);       // Acende LED
    contarPulso();                     // Simula pulso
  } else {
    digitalWrite(ledPin, LOW);        // Apaga LED
  }

  static unsigned long ultimaLeitura = 0;
  if (millis() - ultimaLeitura >= 1000) {
    ultimaLeitura = millis();

    float vazao = (pulsos / 7.5); // fórmula do sensor
    pulsos = 0;

    Serial.print("Vazao: ");
    Serial.print(vazao);
    Serial.println(" L/min");

    lcd.setCursor(0, 1);
    lcd.print("Vazao: ");
    lcd.print(vazao);
    lcd.print(" L/min   ");

    // Controle da válvula
    if (vazao > 0) {
      digitalWrite(valvulaPin, HIGH);
    } else {
      digitalWrite(valvulaPin, LOW);
    }

    // Publicar no ThingsBoard como telemetria (JSON)
    String payload = "{\"vazao\": " + String(vazao, 2) + "}";
    client.publish("v1/devices/me/telemetry", payload.c_str());
  }
}
