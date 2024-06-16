import serial
import time
import csv
from datetime import datetime

# Configura a conexao serial (substitua '/dev/ttyUSB0' pelo dispositivo serial correto)
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
time.sleep(2)  # Aguarda 2 segundos para garantir que a conexao serial esteja estabelecida

# Arquivo CSV para armazenar os valores lidos
arquivo_saida = 'valores_sensor.csv'

# Cria o cabecalho do arquivo CSV
header = ['ID', 'Hora', 'Data', 'Corrente (A)', 'Temperatura (C)', 'Tensao (V)']

try:
    # Abre o arquivo CSV no modo de escrita ('w', newline='') e define o cabecalho
    with open(arquivo_saida, 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(header)
        
        # Loop infinito para ficar escutando os dados seriais
        while True:
            if ser.in_waiting > 0:
                # Le a linha enviada pelo Arduino
                line = ser.readline().decode('utf-8').rstrip()
                
                # Verifica o inicio de cada informacao para armazenar apenas os valores relevantes
                if line.startswith("Corrente medida:"):
                    corrente = float(line.split(":")[1].strip().rstrip("A"))
                    temperatura = float(ser.readline().decode('utf-8').rstrip().split(":")[1].strip().rstrip("C"))
                    tensao = float(ser.readline().decode('utf-8').rstrip().split(":")[1].strip().rstrip("V"))

                    # Obtem a hora e data atuais
                    agora = datetime.now()
                    hora_atual = agora.strftime('%H:%M:%S')
                    data_atual = agora.strftime('%Y-%m-%d')
                    
                    # Gera um ID inico baseado no timestamp atual
                    timestamp = int(datetime.timestamp(agora))
                    
                    # Escreve os dados no arquivo CSV
                    writer.writerow([timestamp, hora_atual, data_atual, corrente, temperatura, tensao])
                    
                    # Mostra no console apenas para debug ou visualizacao
                    print(f"ID: {timestamp}, Hora: {hora_atual}, Data: {data_atual}, Corrente: {corrente} A, Temperatura: {temperatura} C, Tensao: {tensao} V")
                
except KeyboardInterrupt:
    print("Leitura interrompida pelo usuario")
finally:
    ser.close()
