#include "EmonLib.h"
#include "max6675.h"

//----Configuracoes Sensor de Corrente----//
#define CURRENT_CAL 14.40 //VALOR DE CALIBRACAO (DEVE SER AJUSTADO EM PARALELO COM UM MULTIMETRO MEDINDO A CORRENTE DA CARGA)
const int pinoSensor = A0; //PINO ANALOGICO EM QUE O SENSOR ESTA CONECTADO
float ruido = 0.08; //RUIDO PRODUZIDO NA SAIDA DO SENSOR (DEVE SER AJUSTADO COM A CARGA DESLIGADA APOS CARREGAMENTO DO CODIGO NO ARDUINO)

EnergyMonitor emon1; //CRIA UMA INSTANCIA

//----Configuracoes Sensor de Tensao----//
int pinoentrada;
int tensao;
int i=0;
int soma=0;
int media=0;
int resultaTensao=0;

//----Configuracoes Sensor de Temperatura----//

int ktcSO = 8; //PINO DIGITAL (SO)
int ktcCS = 9; //PINO DIGITAL (CS)
int ktcCLK = 10; //PINO DIGITAL (CLK / SCK)

MAX6675 ktc(ktcCLK, ktcCS, ktcSO); //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CLK, CS, SO)

void setup(){  
  Serial.begin(9600); //INICIALIZA A SERIAL
  emon1.current(pinoSensor, CURRENT_CAL); //PASSA PARA A FUNCAO OS PARAMETROS (PINO ANALOGICO / VALOR DE CALIBRACAO)
}

void loop(){
/*---- Configuracoes Sensor de Corrente ----*/  
  emon1.calcVI(17,100); //FUNCAO DE CALCULO (17 SEMICICLOS / TEMPO LIMITE PARA FAZER A MEDICAO)
  double currentDraw = emon1.Irms; //VARIAVEL RECEBE O VALOR DE CORRENTE RMS OBTIDO
  currentDraw = currentDraw-ruido; //VARIAVEL RECEBE O VALOR RESULTANTE DA CORRENTE RMS MENOS O RUIDO
  
  if(currentDraw < 0){ //SE O VALOR DA VARIAVEL FOR MENOR QUE 0, FAZ 
      currentDraw = 0; //VARIAVEL RECEBE 0
  }
/*---- Configuracoes Sensor de Tensao ----*/  
  soma=0;
  i=0;

  if(analogRead(A1)>20){

    for(i=0;i<1000;i++){
      pinoentrada = analogRead(A1);
      tensao = (pinoentrada*6.5)/1024;
      tensao = tensao*1.732;
      soma = (soma+tensao);
    }

    media = soma/10;
 //   Serial.println(media);
    if((media<130)&&(media>70)){
      resultaTensao = 110;
    }
    if(media>150){
      resultaTensao = 220;
    }
    else{
      resultaTensao = 0;
    }
  }
/*---- Configuracoes Sensor de Temperatura ----*/  
   Serial.print("Temperatura: "); //IMPRIME O TEXTO NO MONITOR SERIAL
   Serial.print(ktc.readCelsius()); //IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA
   Serial.println("*C"); //IMPRIME O TEXTO NO MONITOR SERIAL
   delay(500); //INTERVALO DE 500 MILISSEGUNDOS

/*---------- Leitura Serial -----------*/
    Serial.print("Corrente medida: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(currentDraw); //IMPRIME NA SERIAL O VALOR DE CORRENTE MEDIDA
    Serial.println("A"); //IMPRIME O TEXTO NA SERIAL

    Serial.print("Tensão medida: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(resultaTensao); //IMPRIME NA SERIAL O VALOR DE CORRENTE MEDIDA
    Serial.println("V"); //IMPRIME O TEXTO NA SERIAL

    delay(500);
}