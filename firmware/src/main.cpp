#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "config.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("==========================================");
  Serial.println("  Fall Detection IoT — ESP32");
  Serial.println("  Validação do ambiente");
  Serial.println("==========================================");

  Serial.println("\n[OK] ArduinoJson carregado");
  Serial.println("[OK] PubSubClient carregado");
  Serial.println("[OK] WiFi carregado");

  Serial.println("\nConstantes carregadas de config.h:");
  Serial.printf("  WIFI_SSID:          %s\n", WIFI_SSID);
  Serial.printf("  MQTT_BROKER:        %s\n", MQTT_BROKER);
  Serial.printf("  MQTT_PORT:          %d\n", MQTT_PORT);
  Serial.printf("  MQTT_CLIENT_ID:     %s\n", MQTT_CLIENT_ID);
  Serial.printf("  TOPIC_TELEMETRY:    %s\n", TOPIC_TELEMETRY);
  Serial.printf("  TOPIC_ALERT:        %s\n", TOPIC_ALERT);
  Serial.printf("  FALL_THRESHOLD:     %.1f g\n", FALL_THRESHOLD);
  Serial.printf("  REST_THRESHOLD:     %.1f g\n", REST_THRESHOLD);
  Serial.printf("  REST_DURATION_MS:   %d ms\n", REST_DURATION_MS);
  Serial.printf("  SAMPLE_INTERVAL_MS: %d ms\n", SAMPLE_INTERVAL_MS);

  Serial.println("\n[OK] Ambiente configurado com sucesso.");
  Serial.println("Pronto para a Conexão Wi-Fi.");
}

void loop() {
  // implementado nas próximas subetapas
}
