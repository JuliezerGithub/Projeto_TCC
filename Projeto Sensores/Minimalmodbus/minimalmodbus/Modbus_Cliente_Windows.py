import minimalmodbus
import serial

while True:
    # Solicita ao usuário o ID do escravo e o valor do registrador
    id_modbus = input("Digite o ID do escravo: ")
    valor = input("Digite o status do Led (0 ou 1): ")

    try:
        # Converte as entradas para inteiros
        id_modbus = int(id_modbus)
        valor = int(valor)

        # Define parâmetros para a comunicação (Porta Serial, ID do escravo)
        instrument = minimalmodbus.Instrument('COM7', id_modbus)
        instrument.serial.baudrate = 9600  # Configura o baudrate se necessário
        instrument.serial.bytesize = 8
        instrument.serial.parity = serial.PARITY_NONE
        instrument.serial.stopbits = 1
        instrument.serial.timeout = 1  # Timeout em segundos

        # Escreve no registrador
        instrument.write_register(1, valor, 0)

        print(f"Valor {valor} escrito no registrador do escravo com ID {id_modbus}")

    except ValueError:
        print("Por favor, insira valores numéricos válidos para ID e status.")
    except minimalmodbus.NoResponseError:
        print("Nenhuma resposta do escravo. Verifique a conexão e o ID do escravo.")
    except Exception as e:
        print(f"Erro ao comunicar com o dispositivo: {e}")
