#include <Adafruit_ADS1X15.h>
#include <max6675.h>
#include <Modbus.h>
#include <ModbusSerial.h>

// Defina o endereço e ganho do ADS1115
#define ADS1115_ADDRESS 0x48
#define ADS1115_GAIN GAIN_ONE

// Define os pinos do Arduino
int thermoDO = 8;
int thermoCS = 9;
int thermoCLK = 10;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

// Defina os registradores Modbus
const int REG_A0 = 100;
const int REG_A1 = 101;
const int REG_A2 = 102;
const int REG_A3 = 103;
const int REG_TEMP = 104;

// Crie um objeto ADS1115
Adafruit_ADS1115 ads;//(ADS1115_ADDRESS, ADS1115_GAIN);

// Crie um objeto ModbusSerial
ModbusSerial mb;

void setup() {
  // Inicie a comunicação serial
  Serial.begin(9600);

  // Inicialize o ADS1115
  ads.begin();

  // Configure o Modbus Serial
  mb.config(&Serial, 38400, SERIAL_8N1);
  mb.setSlaveId(10);

  // Adicione registradores Modbus
  mb.addIreg(REG_A0);
  mb.addIreg(REG_A1);
  mb.addIreg(REG_A2);
  mb.addIreg(REG_A3);
  mb.addIreg(REG_TEMP);
}

void loop() {

  float tempCelsius = thermocouple.readCelsius();

  // Converta a temperatura para inteiro (opcional, ajuste como necessário)
  int tempInt = tempCelsius * 1000;  // Multiplique por 10 para converter em graus Celsius inteiros

  // Leia os valores analógicos do ADS1115
  int16_t valueA0 = ads.readADC_SingleEnded(0);
  int16_t valueA1 = ads.readADC_SingleEnded(1);
  int16_t valueA2 = ads.readADC_SingleEnded(2);
  int16_t valueA3 = ads.readADC_SingleEnded(3);

  // Converta os valores para inteiros sem sinal de 16 bits
  uint16_t dataA0 = valueA0 + 2048;
  uint16_t dataA1 = valueA1 + 2048;
  uint16_t dataA2 = valueA2 + 2048;
  uint16_t dataA3 = valueA3 + 2048;

  // Escreva os valores nos registradores Modbus
  mb.Ireg(REG_A0, dataA0);
  mb.Ireg(REG_A1, dataA1);
  mb.Ireg(REG_A2, dataA2);
  mb.Ireg(REG_A3, dataA3);
  mb.Ireg(REG_TEMP, tempInt);

  // Lide com a comunicação Modbus
  mb.task();

  // Tempo entre leituras
  delay(1000);
  
}