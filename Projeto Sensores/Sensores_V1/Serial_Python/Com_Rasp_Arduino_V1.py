import serial
import time

# Configura a conexao serial (substitua '/dev/ttyUSB0' pelo dispositivo serial correto)
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
time.sleep(2)  # Aguarda 2 segundos para garantir que a conexao serial esteja estabelecida

# Arquivo para armazenar os valores lidos
arquivo_saida = 'valores_sensor.txt'

try:
    with open(arquivo_saida, 'w') as file:
        while True:
            if ser.in_waiting > 0:
                # Le a linha enviada pelo Arduino
                line = ser.readline().decode('utf-8').rstrip()
                
                # Verifica o inicio de cada informacao para armazenar apenas os valores relevantes
                if line.startswith("Corrente medida:"):
                    corrente = float(line.split(":")[1].strip().rstrip("A"))
                    file.write(f"Corrente: {corrente} A\n")
                elif line.startswith("Tesao:"):
                    tensao = float(line.split(":")[1].strip().rstrip("V"))
                    file.write(f"Tensao: {tensao} V\n")
                elif line.startswith("Temperatura:"):
                    temperatura = float(line.split(":")[1].strip().rstrip(" C"))
                    file.write(f"Temperatura: {temperatura} C\n")
                
                # Mostra no console apenas para debug ou visualizacao
                print(line)
                
except KeyboardInterrupt:
    print("Leitura interrompida pelo usuario")
finally:
    ser.close()
