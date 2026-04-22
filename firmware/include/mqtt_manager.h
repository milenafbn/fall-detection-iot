#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "config.h"
#include "sensor.h"
#include "fall_detector.h"

// MQTT Manager para ThingsBoard
static WiFiClient espClient;
static PubSubClient mqttClient(espClient);

// Função de callback para mensagens MQTT recebidas
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  Serial.printf("[MQTT] Mensagem recebida no tópico: %s\n", topic);
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.printf("[MQTT] Conteúdo: %s\n", message.c_str());
}

// Conecta ao broker MQTT do ThingsBoard
bool mqtt_connect() {
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  mqttClient.setCallback(mqtt_callback);
  mqttClient.setBufferSize(512);

  Serial.printf("[MQTT] Conectando ao ThingsBoard (%s:%d)...\n", MQTT_BROKER, MQTT_PORT);

  int attempts = 0;
  while (!mqttClient.connected()) {
    if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("[MQTT] Conectado ao ThingsBoard com sucesso.");
      return true;
    }
    Serial.printf("[MQTT] Falha (rc=%d). Tentativa %d/5...\n", mqttClient.state(), attempts + 1);
    attempts++;
    if (attempts >= 5) {
      Serial.println("[MQTT] Nao foi possivel conectar ao ThingsBoard.");
      return false;
    }
    delay(2000);
  }
  return true;
}

// Função para verificar e manter a conexão MQTT
void mqtt_check_reconnect() {
  if (!mqttClient.connected()) {
    Serial.println("[MQTT] Conexão perdida. Reconectando...");
    mqtt_connect();
  }
  mqttClient.loop();
}

void mqtt_publish_telemetry(const AccelData& data) {
  if (!mqttClient.connected()) return;

  StaticJsonDocument<256> doc;
  doc["accel_x"]   = serialized(String(data.x, 3));
  doc["accel_y"]   = serialized(String(data.y, 3));
  doc["accel_z"]   = serialized(String(data.z, 3));
  doc["magnitude"] = serialized(String(data.magnitude, 3));
  doc["status"]    = "normal";

  char buffer[256];
  serializeJson(doc, buffer);

  mqttClient.publish(TB_TOPIC_TELEMETRY, buffer);
  Serial.printf("[MQTT] Telemetria enviada ao ThingsBoard: %s\n", buffer);
}

void mqtt_publish_alert(const FallEvent& event) {
  if (!mqttClient.connected()) return;

  StaticJsonDocument<256> doc;
  doc["fall_detected"]    = true;
  doc["impact_magnitude"] = serialized(String(event.impact_magnitude, 3));
  doc["timestamp"]        = event.timestamp;
  doc["device_id"]        = MQTT_CLIENT_ID;

  char buffer[256];
  serializeJson(doc, buffer);

  mqttClient.publish(TB_TOPIC_ALERT, buffer);

  Serial.println("[MQTT] ==========================================");
  Serial.println("[MQTT] ALERTA DE QUEDA ENVIADO AO THINGSBOARD");
  Serial.printf("[MQTT] Tópico: %s\n", TB_TOPIC_ALERT);
  Serial.printf("[MQTT] Payload: %s\n", buffer);
  Serial.println("[MQTT] ==========================================");
}
