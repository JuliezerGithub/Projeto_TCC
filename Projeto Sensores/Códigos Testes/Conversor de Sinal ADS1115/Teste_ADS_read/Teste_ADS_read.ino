#include "ADS1X15.h"

ADS1115 ADS(0x48);


void setup() 
{
  Serial.begin(115200);                        // Inicializa a comunicação serial a 115200 bps.
  Serial.println(__FILE__);                    // Imprime o nome do arquivo no monitor serial.
  Serial.print("ADS1X15_LIB_VERSION: ");       
  Serial.println(ADS1X15_LIB_VERSION);         // Imprime a versão da biblioteca.

  Wire.begin();                                // Inicializa a comunicação I2C.
  ADS.begin();                                 // Inicializa o ADS1115.
}

void loop() 
{
  ADS.setGain(0);                              // Define o ganho do ADS1115. O ganho '0' refere-se a uma faixa de ±6.144V.

  int16_t val_0 = ADS.readADC(0);              // Lê o valor digital da entrada analógica AIN0.
  int16_t val_1 = ADS.readADC(1);              // Lê o valor digital da entrada analógica AIN1.
  int16_t val_2 = ADS.readADC(2);              // Lê o valor digital da entrada analógica AIN2.
  int16_t val_3 = ADS.readADC(3);              // Lê o valor digital da entrada analógica AIN3.

  float f = ADS.toVoltage(1);                  // Obtém o fator de conversão para transformar o valor digital em tensão.

  Serial.print("\tAnalog0: "); 
  Serial.print(val_0);                         // Imprime o valor digital bruto lido da entrada AIN0.
  Serial.print('\t'); 
  Serial.println(val_0 * f, 3);                // Converte e imprime o valor da leitura em volts com 3 casas decimais.

  Serial.print("\tAnalog1: "); 
  Serial.print(val_1);                         // Mesma sequência para a entrada AIN1.
  Serial.print('\t'); 
  Serial.println(val_1 * f, 3);

  Serial.print("\tAnalog2: "); 
  Serial.print(val_2);                         // Mesma sequência para a entrada AIN2.
  Serial.print('\t'); 
  Serial.println(val_2 * f, 3);

  Serial.print("\tAnalog3: "); 
  Serial.print(val_3);                         // Mesma sequência para a entrada AIN3.
  Serial.print('\t'); 
  Serial.println(val_3 * f, 3);

  Serial.println();                            // Linha em branco para separar as leituras.

  delay(1000);                                 // Espera de 1 segundo antes de fazer novas leituras.
}



//  -- END OF FILE --

