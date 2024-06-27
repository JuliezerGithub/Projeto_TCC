#include <ModbusRtu.h>

// Definições
uint16_t au16data[16]; // Buffer de dados
Modbus slave(1, Serial); // Id do dispositivo, objeto Serial

void setup() {
    // Inicializa a comunicação serial
    Serial.begin(9600);
    slave.begin(9600); // Inicia a comunicação Modbus
}

void loop() {
    // Lê e processa os pedidos Modbus
    slave.poll(au16data, 16);
    // Atualize os dados conforme necessário
    au16data[0] = analogRead(A0);
    //au16data[0] = 100;
}
