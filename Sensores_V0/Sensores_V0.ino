/*******************************************************************************
* Título: Sensores
* Versão: 0
* Data: 08/04/2024
* Descrição: Código que faz o arduino ler dois sensores ao mesmo tempo
*  - Sensor de corrente ACS712 - 5A
*  - Sensor de temperatura MAX6675
*******************************************************************************/
#include "EmonLib.h"
#include "max6675.h"

//Variáveis Sensor Corrente

#define CURRENT_CAL 18.40                       //VALOR DE CALIBRAÇÃO (DEVE SER AJUSTADO EM PARALELO COM UM MULTÍMETRO MEDINDO A CORRENTE DA CARGA)
const int pinoSensor = A2;                      //PINO ANALÓGICO EM QUE O SENSOR ESTÁ CONECTADO
float ruido = 0.0595;                           //RUÍDO PRODUZIDO NA SAÍDA DO SENSOR (DEVE SER AJUSTADO COM A CARGA DESLIGADA APÓS CARREGAMENTO DO CÓDIGO NO ARDUINO)

EnergyMonitor emon1;                            //CRIA UMA INSTÂNCIA

//Variáveis Sensor de Termopar

int ktcSO = 8;                                  //PINO DIGITAL (SO)
int ktcCS = 9;                                  //PINO DIGITAL (CS)
int ktcCLK = 10;                                //PINO DIGITAL (CLK / SCK)

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);              //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CLK, CS, SO)

void setup(){  
  Serial.begin(9600);                           //INICIALIZA A SERIAL
  emon1.current(pinoSensor, CURRENT_CAL);       //PASSA PARA A FUNÇÃO OS PARÂMETROS (PINO ANALÓGIO / VALOR DE CALIBRAÇÃO)
  delay(500);                                   //INTERVALO DE 500 MILISSEGUNDOS
}
void loop(){
  emon1.calcVI(17,100);                         //FUNÇÃO DE CÁLCULO (17 SEMICICLOS / TEMPO LIMITE PARA FAZER A MEDIÇÃO)
  double currentDraw = emon1.Irms;              //VARIÁVEL RECEBE O VALOR DE CORRENTE RMS OBTIDO
  currentDraw = currentDraw-ruido;              //VARIÁVEL RECEBE O VALOR RESULTANTE DA CORRENTE RMS MENOS O RUÍDO
 
  if(currentDraw < 0){                          //SE O VALOR DA VARIÁVEL FOR MENOR QUE 0, FAZ 
      currentDraw = 0;                          //VARIÁVEL RECEBE 0
  }
    Serial.println("");
    Serial.print("Corrente medida: ");          
    Serial.print(currentDraw,4);                //IMPRIME NA SERIAL O VALOR DE CORRENTE MEDIDA COM 4 CASAS DECIMAIS
    Serial.println("A");                        
    delay(500);
    Serial.print("Temperatura: ");              
    Serial.print(ktc.readCelsius());            //IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA EM ºC
    Serial.println("°C");                       
    delay(500);                                 //INTERVALO DE 500 MILISSEGUNDOS
}
