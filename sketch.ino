#include <WiFi.h>
#include <PubSubClient.h>

// ===== CONFIGURAÇÃO WI-FI =====
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ===== CONFIGURAÇÃO MQTT =====
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_client_id = "ESP32_Iluminacao_Publica_Isabella_2026";

// ===== TÓPICOS MQTT =====
const char* topic_luminosidade = "iluminacao/luminosidade";
const char* topic_led = "iluminacao/led";
const char* topic_intensidade = "iluminacao/intensidade";

// ===== PINOS =====
#define LDR_PIN 34       // Pino ADC para leitura do sensor LDR
#define LED_PIN 2        // Pino GPIO para controle do LED

// ===== LIMITES DE LUMINOSIDADE =====
// Valores menores indicam ambiente mais escuro
const int LDR_ESCURO = 300;
const int LDR_CLARO = 3000;

// ===== OBJETOS =====
WiFiClient espClient;
PubSubClient client(espClient);

// ===== VARIÁVEIS =====
unsigned long ultimoEnvio = 0;
const long intervaloEnvio = 1000;

// ===== FUNÇÃO: Conectar ao Wi-Fi =====
void conectarWiFi() {
  Serial.print("Conectando ao Wi-Fi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

// ===== FUNÇÃO: Conectar ao Broker MQTT =====
void conectarMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT...");

    if (client.connect(mqtt_client_id)) {
      Serial.println(" conectado!");
      Serial.println("Cliente MQTT pronto para publicar dados.");
    } else {
      Serial.print(" falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

// ===== FUNÇÃO: Calcular intensidade do LED =====
int calcularIntensidadeLED(int valorLDR) {
  valorLDR = constrain(valorLDR, LDR_ESCURO, LDR_CLARO);

  // Quanto menor o valor do LDR, mais escuro está o ambiente
  // Quanto mais escuro, maior será a intensidade do LED
  int intensidade = map(valorLDR, LDR_ESCURO, LDR_CLARO, 255, 0);

  return intensidade;
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);

  Serial.println("==============================================");
  Serial.println("Sistema Inteligente de Iluminação Pública");
  Serial.println("IoT + ESP32 + LDR + LED gradual + MQTT");
  Serial.println("==============================================");
  Serial.println();

  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  conectarWiFi();

  client.setServer(mqtt_server, mqtt_port);
}

// ===== LOOP PRINCIPAL =====
void loop() {
  if (!client.connected()) {
    conectarMQTT();
  }

  client.loop();

  unsigned long agora = millis();

  if (agora - ultimoEnvio >= intervaloEnvio) {
    ultimoEnvio = agora;

    int valorLDR = analogRead(LDR_PIN);
    int intensidadeLED = calcularIntensidadeLED(valorLDR);

    // Controle gradual do brilho do LED
    analogWrite(LED_PIN, intensidadeLED);

    String estadoLED;

    if (intensidadeLED == 0) {
      estadoLED = "OFF";
    } else if (intensidadeLED < 100) {
      estadoLED = "BAIXA";
    } else if (intensidadeLED < 200) {
      estadoLED = "MEDIA";
    } else {
      estadoLED = "ALTA";
    }

    char msgLuminosidade[10];
    char msgIntensidade[10];

    sprintf(msgLuminosidade, "%d", valorLDR);
    sprintf(msgIntensidade, "%d", intensidadeLED);

    client.publish(topic_luminosidade, msgLuminosidade);
    client.publish(topic_led, estadoLED.c_str());
    client.publish(topic_intensidade, msgIntensidade);

    Serial.print("Luminosidade (LDR): ");
    Serial.print(valorLDR);
    Serial.print(" | Intensidade LED: ");
    Serial.print(intensidadeLED);
    Serial.print("/255");
    Serial.print(" | Estado: ");
    Serial.print(estadoLED);
    Serial.println(" | Dados publicados via MQTT");
  }
}
