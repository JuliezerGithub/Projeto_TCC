import serial

ser = serial.Serial("/dev/ttyS0" , 9600)

dado_arduino = str()
dado_valido = str()
controle = ""

while True:
    print("Aguardando dado do Arduino...")
    dado_arduino = ser.read()
    dado_valido = dado_arduino[0]
    dado_valido = int(dado_valido)
    print(dado_valido)
    if(dado_valido==97):
        print("Função 01 -Reconhecimento FACIAL")