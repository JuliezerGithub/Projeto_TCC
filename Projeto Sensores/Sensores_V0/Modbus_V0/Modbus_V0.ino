/*  
  Modbus RTU Server para Arduino UNO / MEGA.
  
  Arduino recebe requisicoes Modbus RTU pela Serial/USB ou Modulo RS-485.
  
  Porta Serial:
  O servidor Modbus utiliza a interface Serial padrao. Nao usar esta mesma Serial para debug!
  
  Para usar com modulo RS-485 (conversor RS-485/TTL):
  A biblioteca ArduinoRS485 utiliza o pino 2 ligado ao pino RE e DE do modulo RS485/TTL.

  Instalar as bibliotecas:
  ArduinoModbus (by Arduino). Versao 1.0.7
  ArduinoRS485 (by Arduino). Versao 1.0.4
  
  Referencias:
  https://www.arduino.cc/en/ArduinoModbus/ArduinoModbus
  https://www.arduino.cc/en/Reference/ArduinoRS485
  
  Licenca MIT - conforme arquivo LICENCE.TXT

  Link do circuito basico no TinkerCAD
  https://www.tinkercad.com/things/j5SwQB4B2Nx
  
  modificado 15 set 2023
  by Gustavo Kunzel
  https://kikee.com.br/ensino-de-engenharia
*/

// Bibliotecas
#include <ArduinoRS485.h>   // ArduinoModbus depende da lib ArduinoRS485 (instalar via gerenciador)
#include <ArduinoModbus.h>  // Lib Arduino Modbus (instalar via gerenciador)

// Definicoes do escravo e da comunicao serial
#define SLAVE_ID 1              // endereco do escravo Modbus RTU
#define BAUDRATE 57600          // 57600 bps
#define UART_CONFIG SERIAL_8N2  // 8 data bits, sem paridade, 2 stop bits

// Definicoes de pinos utilizados
#define NUMBER_DIGITAL_INPUTS 2     // 2 entradas digitais (discrete inputs - bit)
#define PIN_DISCRETE_INPUT_1 3      // digital input 1 no pino 3
#define PIN_DISCRETE_INPUT_2 4
#define NUMBER_INPUT_REGISTERS 2    // 2 entradas analogicas (inputs registers - 16 bits)
#define PIN_INPUT_REGISTER_1 A0     // input register 1 no pino A0
#define PIN_INPUT_REGISTER_2 A1
#define NUMBER_COILS 2              // 2 saidas digitais (coils - bit)
#define PIN_COIL_1 7                // coil 1 no pino 7
#define PIN_COIL_2 9
#define NUMBER_HOLDING_REGISTERS 4  // 4 registradores de dados (holding registers - 16 bits)
#define PIN_HOLDING_REGISTER_PWM1 5 
#define PIN_HOLDING_REGISTER_PWM2 6

// enderecos iniciais dos registradores para tipo de dado
#define DIGITAL_INPUT_ADDRESS     100  // 16 enderecos para cada tipo de dado
#define ANALOG_INPUT_ADDRESS      200
#define COIL_ADDRESS              300
#define HOLDING_REGISTER_ADDRESS  400

/*
 * Configuracoes do Arduino
 */
void setup() {

  //*******************************************************
  // configura pinos de entradas e saidas
  // configura entradas digitais com resistor de pullup
  pinMode(PIN_DISCRETE_INPUT_1, INPUT_PULLUP);
  pinMode(PIN_DISCRETE_INPUT_2, INPUT_PULLUP);

  // configura saidas e seta o estado inicial delas para 0
  pinMode(PIN_COIL_1, OUTPUT);
  pinMode(PIN_COIL_2, OUTPUT);
  digitalWrite(PIN_COIL_1, LOW);
  digitalWrite(PIN_COIL_2, LOW);

  // configura saidas analogicas pwm e zera elas
  analogWrite(PIN_HOLDING_REGISTER_PWM1,0);
  analogWrite(PIN_HOLDING_REGISTER_PWM2,0);

  // configura led embutido como saida (para testes de holding registers)
  pinMode(LED_BUILTIN, OUTPUT);

  //*******************************************************
  // configura o servidor Modbus RTU
  // Inicializa o servidor com o endereco de escravo SLAVE_ID e as configuracoes de taxa
  if (!ModbusRTUServer.begin(SLAVE_ID, BAUDRATE, UART_CONFIG)) {
    Serial.println("Falhou iniciar o Servidor Modbus RTU!");
    while (1)
      ;  // para o programa se deu erro no servidor
  }
  // associa os enderecos de registradores do servidor modbus para as entradas e saídas definidas
  // entradas digitais a partir do endereço DIGITAL_INPUT_ADDRESS
  ModbusRTUServer.configureDiscreteInputs(DIGITAL_INPUT_ADDRESS, NUMBER_DIGITAL_INPUTS);
  // entradas analogicas a partir do endereço ANALOG_INPUT_ADDRESS
  ModbusRTUServer.configureInputRegisters(ANALOG_INPUT_ADDRESS, NUMBER_INPUT_REGISTERS);
  // bobinas a partir do endereço COIL_ADDRESS
  ModbusRTUServer.configureCoils(COIL_ADDRESS, NUMBER_COILS);
  // associa holding registers (saidas analogicas pwm e registradores) a partir do endereco da ultima saida pwm
  ModbusRTUServer.configureHoldingRegisters(HOLDING_REGISTER_ADDRESS, NUMBER_HOLDING_REGISTERS);
}

/*
* Laco principal
* sincroniza entradas e saidas com o Modbus RTU Server
*/
void loop() {
  //*******************************************************
  // Checa por requisicoes Modbus RTU recebidas e atualiza dados no servidor
  ModbusRTUServer.poll();

  //*******************************************************
  // rotina de atualizacoes de ENTRADAS
  // atualiza o estado das entradas mapeadas na memoria do servidor

  // entradas digitais
  // le o estado do pino e atualiza no servidor
  ModbusRTUServer.writeDiscreteInputs(DIGITAL_INPUT_ADDRESS + 0, digitalRead(PIN_DISCRETE_INPUT_1), 1); // 0x0000
  ModbusRTUServer.writeDiscreteInputs(DIGITAL_INPUT_ADDRESS + 1, digitalRead(PIN_DISCRETE_INPUT_2), 1); // 0x0001
  
  // entradas analogicas
  // le o sinal analogico e atualiza no servidor
  uint16_t tempRead;
  tempRead = analogRead(PIN_INPUT_REGISTER_1);  
  ModbusRTUServer.writeInputRegisters(ANALOG_INPUT_ADDRESS + 0, &tempRead, 1);  //0x0010
  tempRead = analogRead(PIN_INPUT_REGISTER_2);  
  ModbusRTUServer.writeInputRegisters(ANALOG_INPUT_ADDRESS + 1, &tempRead, 1);  //0x0011

  //*******************************************************
  // rotina de atualizacoes de SAIDAS
  // escreve estado das saidas mapeadas conforme a memoria atual do servidor

  // atualiza saidas digitais
  // atualiza o pino digital conforme o estado da bobina no servidor
  digitalWrite(PIN_COIL_1, ModbusRTUServer.coilRead(COIL_ADDRESS + 0)); // 0x0020
  digitalWrite(PIN_COIL_2, ModbusRTUServer.coilRead(COIL_ADDRESS + 1)); // 0x0021
  
  // atualiza saidas PWM
  // atualiza pwm do pino conforme o estado da bobina no servidor
  analogWrite(PIN_HOLDING_REGISTER_PWM1, ModbusRTUServer.holdingRegisterRead(HOLDING_REGISTER_ADDRESS + 0)); // 0x0030
  analogWrite(PIN_HOLDING_REGISTER_PWM2, ModbusRTUServer.holdingRegisterRead(HOLDING_REGISTER_ADDRESS + 1)); // 0x0031

  //*******************************************************
  // teste de leitura dos holding registers (word, 16 bits)
  // obtem o valor do primeiro holding register (depois das saidas pwm, offset 0)
  // se o valor armazenado eh maior que 1000, liga o LED_BUILTIN
  uint16_t testValue;
  testValue = ModbusRTUServer.holdingRegisterRead(HOLDING_REGISTER_ADDRESS + 2); //0x0032
  if (testValue > 1000) digitalWrite(LED_BUILTIN, HIGH);
  else digitalWrite(LED_BUILTIN, LOW);

  // teste de escrita dos holding registers
  // o holding register guarda o tempo decorrido em segundos desde a inicializacao do Arduino
  uint16_t seconds = millis() / 1000;
  ModbusRTUServer.holdingRegisterWrite(HOLDING_REGISTER_ADDRESS + 3, seconds);  // 0x0033
  //*******************************************************
}
