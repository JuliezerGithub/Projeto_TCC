// this example is public domain. enjoy!
// https://learn.adafruit.com/thermocouple/

#include "max6675.h"
#include <Modbus.h>
#include <ModbusSerial.h>

// Define os pinos do Arduino
int thermoDO = 8;
int thermoCS = 9;
int thermoCLK = 10;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

// Defina os parâmetros Modbus
const int REG_TEMP = 100;  // Endereço do registrador Modbus para temperatura

ModbusSerial mb;            // Crie uma instância ModbusSerial

void setup() {

  // Configure o Modbus Serial
  mb.config(&Serial, 38400, SERIAL_8N1);
  mb.setSlaveId(10);
  mb.addIreg(REG_TEMP);
}

void loop() {

  float tempCelsius = thermocouple.readCelsius();

  // Converta a temperatura para inteiro (opcional, ajuste como necessário)
  int tempInt = tempCelsius * 1000;  // Multiplique por 10 para converter em graus Celsius inteiros

  // Escreva a temperatura no registrador Modbus
  mb.Ireg(REG_TEMP, tempInt);

  // Lide com a comunicação Modbus
  mb.task();

  // Tempo entre leituras
  delay(1000);
}
