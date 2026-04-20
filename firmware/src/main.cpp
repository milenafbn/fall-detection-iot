#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "config.h"
#include "wifi_manager.h"
#include "sensor.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("==========================================");
  Serial.println("  Fall Detection IoT — ESP32");
  Serial.println("  Simulação do MPU6050");
  Serial.println("==========================================");

  wifi_connect();

  Serial.println("\n[Sensor] Iniciando simulação do MPU6050...");
  Serial.println("[Sensor] Ciclo: 4s normal → 0.3s queda → 2s repouso\n");
}

void loop() {
  wifi_check_reconnect();

  AccelData data = sensor_read();
  sensor_print(data);

  delay(SAMPLE_INTERVAL_MS);
}
