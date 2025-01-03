/*******************************************************************************
* Título: Sensores
* Versão: 1
* Data: 17/04/2024
* Descrição: Código que faz o arduino ler dois sensores ao mesmo tempo utilizando
* o ADS1115.
*  - Sensor de corrente ACS712 - 5A
*  - Sensor de temperatura MAX6675
*******************************************************************************/

#include "ADS1X15.h"
#include "EmonLib.h"
#include "max6675.h"

//Protocolo I2C
ADS1115 ADS(0x48);
  
//Variáveis Sensor Corrente

#define CURRENT_CAL 14.40                       //VALOR DE CALIBRAÇÃO (DEVE SER AJUSTADO EM PARALELO COM UM MULTÍMETRO MEDINDO A CORRENTE DA CARGA)
const int pinoSensorAC = 0;                     //PINO ANALÓGICO EM QUE O SENSOR CORRENTE ESTÁ CONECTADO
const int pinoSensorV = 0;                      //PINO ANALÓGICO EM QUE O SENSOR CORRENTE ESTÁ CONECTADO
float ruido = 0.08; ;//0.0595   1.1595        //RUÍDO PRODUZIDO NA SAÍDA DO SENSOR (DEVE SER AJUSTADO COM A CARGA DESLIGADA APÓS CARREGAMENTO DO CÓDIGO NO ARDUINO)

EnergyMonitor emon1;                            //CRIA UMA INSTÂNCIA

//Variáveis Sensor de Termopar

int ktcSO = 8;                                  //PINO DIGITAL (SO)
int ktcCS = 9;                                  //PINO DIGITAL (CS)
int ktcCLK = 10;                                //PINO DIGITAL (CLK / SCK)

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);              //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CLK, CS, SO)444

void setup() 
{
  Serial.begin(9600);
  Serial.println(__FILE__);
  //Serial.print("ADS1X15_LIB_VERSION: ");
  //Serial.println(ADS1X15_LIB_VERSION);
  Serial.print("V1 INICIANDO... ");
  delay(1000);
  Wire.begin();
  ADS.begin();

  emon1.current(pinoSensorAC, CURRENT_CAL);       //PASSA PARA A FUNÇÃO OS PARÂMETROS (PINO ANALÓGIO / VALOR DE CALIBRAÇÃO)
  delay(500);    
}


void loop() 
{
  ADS.setGain(0);

  //int16_t val_0 = ADS.readADC(0);  
  //int16_t val_1 = ADS.readADC(1);  
  int16_t val_2 = ADS.readADC(2);  
  int16_t val_3 = ADS.readADC(3);  
  int16_t pinoSensorAC = ADS.readADC(0);
  int16_t pinoSensorV = ADS.readADC(1);
  float f = ADS.toVoltage(1);  //  voltage factor

  //Serial.print("\tAnalog0: "); Serial.print(val_0); Serial.print('\t'); Serial.println(val_0 * f, 3);
  //Serial.print("\tAnalog1: "); Serial.print(val_1); Serial.print('\t'); Serial.println(val_1 * f, 3);
  //Serial.print("\tAnalog2: "); Serial.print(val_2); Serial.print('\t'); Serial.println(val_2 * f, 3);
  //Serial.print("\tAnalog3: "); Serial.print(val_3); Serial.print('\t'); Serial.println(val_3 * f, 3);
  //Serial.println();

  delay(500);
  emon1.calcVI(17,100);                         //FUNÇÃO DE CÁLCULO (17 SEMICICLOS / TEMPO LIMITE PARA FAZER A MEDIÇÃO)
  double currentDraw = emon1.Irms;              //VARIÁVEL RECEBE O VALOR DE CORRENTE RMS OBTIDO
  currentDraw = currentDraw-ruido;
  if(currentDraw < 0){                          //SE O VALOR DA VARIÁVEL FOR MENOR QUE 0, FAZ 
      currentDraw = 0;                          //VARIÁVEL RECEBE 0
  }
    Serial.println("");
    Serial.print("Corrente medida: ");          
    Serial.print(currentDraw,4);                //IMPRIME NA SERIAL O VALOR DE CORRENTE MEDIDA COM 4 CASAS DECIMAIS
    Serial.println("A");                        
    //delay(100);
    Serial.print("Temperatura: ");              
    Serial.print(ktc.readCelsius());            //IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA EM ºC
    Serial.println(" C");                     
    //delay(100);                                 //INTERVALO DE 500 MILISSEGUNDOS
    Serial.print("Tesao: ");              
    Serial.print(pinoSensorV * f, 3);            //IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA EM ºC
    Serial.println("V");
    Serial.println("");                       
    delay(100);

}


//  -- END OF FILE --

