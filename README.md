# Monitoramento de Quedas com IoT

Sistema distribuído para detecção automática de quedas utilizando Internet das Coisas (IoT), desenvolvido para a disciplina de Sistemas Distribuídos.

## Visão Geral

O projeto implementa uma arquitetura distribuída em três camadas para detectar eventos de queda e enviar alertas em tempo real:

- Edge Layer: coleta e pré-processamento com ESP32 + MPU6050  
- Communication Layer: transmissão via MQTT  
- Cloud/Middleware Layer: monitoramento e alertas com ThingsBoard  

## Tecnologias

- ESP32
- MPU6050
- MQTT
- ThingsBoard
- Arduino IDE / PlatformIO
- Git e GitHub

## Arquitetura

Fluxo do sistema:

Sensor (MPU6050)  
↓  
ESP32 (detecção local)  
↓  
MQTT Broker  
↓  
ThingsBoard  
↓  
Dashboard + Alertas

## Funcionalidades

- Captura de dados inerciais
- Detecção de quedas
- Envio de eventos em tempo real
- Monitoramento por dashboard
- Geração de alertas

## Estrutura do Projeto
