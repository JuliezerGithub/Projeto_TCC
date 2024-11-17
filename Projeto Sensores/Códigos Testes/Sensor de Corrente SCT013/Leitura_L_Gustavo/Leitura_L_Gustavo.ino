float corrente_inst[300];
float corrente_pico;
float corrente_eficaz;
double maior_valor = 0;
double corrente_valor = 0;
int pino_sensor = A0;

void setup() {
  Serial.begin(9600);
  pinMode(pino_sensor, INPUT);
}

void loop() {
  //Zerar Valores
  maior_valor = 0;

  //Armazena 300 Leituras da ONDA SENOIDAL
  for (int i = 0; i < 300; i++) {
    corrente_inst[i] = analogRead(pino_sensor);
    delayMicroseconds(600);
  }

  for (int i = 0; i < 300; i++) {
    if (maior_valor < corrente_inst[i]) {
      maior_valor = corrente_inst[i];
    }
  }
  Serial.print("Maior Valor: ");
  Serial.println(maior_valor);

  //Transforma o maior valor em corrente de pico
  corrente_pico = maior_valor - 932;       //Para o zero em 2,5V. Precisa remover o OFFSET
  corrente_pico = maior_valor * 4.882812;  //Resolução mínima de leitura do arduino é de 4,8mv

  corrente_pico = corrente_pico / 1428;

  Serial.print("Corrente de Pico:");
  Serial.print(corrente_pico);
  Serial.print(" A");
  Serial.print(" --- ");
  Serial.print(corrente_pico * 1000);
  Serial.println(" mA");


  //Converte para Corrente Eficaz
  corrente_eficaz = corrente_pico / 1.4;
  Serial.print("Corrente de Eficaz:");
  Serial.print(corrente_eficaz);
  Serial.print(" A");
  Serial.print(" --- ");
  Serial.print(corrente_eficaz * 1000);
  Serial.println(" mA");
  delay(1000);
}