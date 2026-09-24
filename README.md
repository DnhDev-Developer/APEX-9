#APEX-9

Autonomous Precision & EXtreme — 9 Sensors

Robô autônomo de alta velocidade desenvolvido para competições de Line Follower, com foco em precisão, estabilidade, velocidade e evolução modular.

Objetivo:

Desenvolver uma plataforma própria capaz de acompanhar linhas em alta velocidade, utilizando controle em tempo real e dados dos sensores para otimizar continuamente o desempenho.

Hardware:
MCU: STM32F103C8T6
Sensores de linha: 9× QRE1113
Motores: 2× Micro Motor 6 V 750 RPM com encoder
Driver: TB6612FNG
IMU: ICM-42688-P
Distância: 2× VL53L0X
Cor: TCS34725
Monitoramento: INA226
Armazenamento: microSD
Bateria: LiPo 2S 7,4 V 2200 mAh 30C
Chassi e rodas: impressão 3D

Software:

Arquitetura modular desenvolvida em C/C++, separando:

Motor
Encoder
QRE1113
PID
LineFollower
TCS34725
VL53L0X
IM
INA226
Telemetry
Logger
Intersection
