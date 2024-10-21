//Sensor de Corrente ACS712 medindo Corrente AC, Potencia e Energia 
//Por GE Projetos e Tutoriais

float tensaoAC = 220.000; //Defina aqui a tensão AC da rede
float correnteRms; //A variável que vai armazenar a corrente medida pelo sensor
float potencia; //A variável que vai armazenar potência a partir da fórmula P = V x I
float energia=0; //A variável que vai armazenar a energia gasta a partir da fórmula E = P x t 

//Defina a variável 'sensibilidade' a partir da corrente medida pelo seu sensor:
//- Para 30A, sensibilidade = 0.066; 
//- Para 20A, sensibilidade = 0.100; 
//- Para 5A,  sensibilidade = 0.185;
float sensibilidade = 0.185; 

void setup() {
  Serial.begin(9600); //Identifica que o display possui 20 colunas e 4 linhas
}

void loop() {
  correnteRms = calculaCorrente(filtroDaMedia()); //Calcula a corrente
  potencia = abs(correnteRms * tensaoAC); //Calcula a potência a partir da fórmula P = V x I. A potência é apresentada em valor absoluto pela função "abs"
  energia+=(potencia*1.2/1000); //Calcula a energia gasta até o momento a partir da fórmula E = P x t  ____  t = 1,2s ,pois esse é o tempo aproximado de ciclo da função loop desse programa
  Serial.print("Tensao:    ");
  Serial.print(tensaoAC,3);
  Serial.println(" V");
  //Digita o valor de Corrente na linha 2
  Serial.print("Corrente:  ");
  Serial.print(correnteRms,3);
  Serial.println(" A");
  Serial.println(analogRead(A0));
  //Digita o valor da Potência na linha 3
  Serial.print("Potencia:  ");
  Serial.print(potencia,3);
  Serial.println(" W"); 
  //Digita a energia gasta até o momento na linha 4
  Serial.print("Energia:   ");
  Serial.print(energia,3);
  Serial.println(" kJ");
  Serial.println();
}

// A função "calculaCorrente" vai converter o sinal amostrado pelo arduino em A0 num valor de corrente.
float calculaCorrente(int sinalSensor) {
  return (float)(sinalSensor)*(5.000)/(1023.000*sensibilidade);
}

// A função "filtroDaMedia", como o nome já diz, é um Filtro da Média. Esse é um filtro digital que serve para retirar o ruído do sinal do sensor.
// Nessa função, nós amostramos o sinal do sensor mil vezes, somamos essas amostras e dividimos por 1000. Obtemos assim a média aritmética de 1000 amostras.
int filtroDaMedia(){
  long somaDasCorrentes=0, mediaDasCorrentes;
  for(int i=0; i<1000; i++){
    somaDasCorrentes+=pow((analogRead(A2)-509),2); //Soma o valor das correntes elevadas ao quadrado para calcular o valor RMS
    delay(1);
  }
  mediaDasCorrentes=sqrt(somaDasCorrentes/1000); //Calcula a média quadrática da corrente
  if(mediaDasCorrentes==1) //esse if é para remover o ruído de 7mA quando I=0. possui uma desvantagem, pois só permite que o sensor meça correntes a partir de (2*5)/(1023*sensibilidade)
  return 0;
  return mediaDasCorrentes;
}
