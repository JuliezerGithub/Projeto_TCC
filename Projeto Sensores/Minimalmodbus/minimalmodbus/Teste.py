#!/usr/bin/env python3
import minimalmodbus
import serial
import time

id_modbus = input("Digite o ID do escravo: ")
while True:
    # Solicita ao usuário o ID do escravo e o valor do registrador
    #id_modbus = input("Digite o ID do escravo: ")
    # Leitura do registrador 0
    registrador = 0  # Registrador que queremos ler
    numero_decimais = 1 # Número de casas decimais esperadas no valor

    try:
        # Converte as entradas para inteiros
        id_modbus = int(id_modbus)

        # Define parâmetros para a comunicação (Porta Serial, ID do escravo)
        instrument = minimalmodbus.Instrument('COM7', id_modbus)
        instrument.serial.baudrate = 9600  # Configura o baudrate se necessário
        instrument.serial.bytesize = 8
        instrument.serial.parity = serial.PARITY_NONE
        instrument.serial.stopbits = 1
        instrument.serial.timeout = 1  # Timeout em segundos

        # Lê o valor do registrador especificado
        valor_registrador = instrument.read_register(registrador, numero_decimais)

        # Exibe o valor lido
        print(f'Valor do registrador {registrador}: {valor_registrador}')

    except ValueError:
        print("Por favor, insira valores numéricos válidos para ID e status.")
    except minimalmodbus.NoResponseError:
        print("Nenhuma resposta do escravo. Verifique a conexão e o ID do escravo.")
    except Exception as e:
        print(f"Erro ao comunicar com o dispositivo: {e}")
    #Espera por:
    time.sleep(0.5)