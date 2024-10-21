int pinoentrada;
int tensao;
int i=0;
int soma=0;
int media=0;

void setup() {              
  pinMode(A0,INPUT);
  Serial.begin(9600);

}

void loop() {
  soma=0;
  i=0;

  if(analogRead(A0)>20){

    for(i=0;i<1000;i++){
      pinoentrada = analogRead(A0);
      tensao = (pinoentrada*6.5)/1024;
      tensao = tensao*1.732;
      soma = (soma+tensao);
    }

    media = soma/10;
 //   Serial.println(media);
    if((media<130)&&(media>70)){
      Serial.println("110V");
      Serial.println(media);
    }
    if(media>150){
      Serial.println("220V");
      Serial.println(media);
    }
    delay(2000);
  }

}