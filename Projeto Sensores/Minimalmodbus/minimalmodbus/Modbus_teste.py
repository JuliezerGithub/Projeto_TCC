import minimalmodbus
import serial

# Configuração do instrumento Modbus
instrument = minimalmodbus.Instrument('COM7', 10)  # Porta serial e ID do escravo
instrument.serial.baudrate = 9600  # Baudrate igual ao configurado no Arduino
instrument.serial.bytesize = 8
instrument.serial.parity = serial.PARITY_NONE
instrument.serial.stopbits = 1
instrument.serial.timeout = 1  # Timeout de 1 segundo

# Registradores Modbus no Arduino (definidos no código do Arduino)
REG_A0 = 100
REG_A1 = 101
REG_A2 = 102
REG_A3 = 103
REG_TEMP = 104

def ler_dados_modbus():
    try:
        # Leitura dos valores do ADS1115 (valores analógicos)
        dataA0 = instrument.read_register(REG_A0, 0)  # Registrador 100 (A0)
        dataA1 = instrument.read_register(REG_A1, 0)  # Registrador 101 (A1)
        dataA2 = instrument.read_register(REG_A2, 0)  # Registrador 102 (A2)
        dataA3 = instrument.read_register(REG_A3, 0)  # Registrador 103 (A3)
        
        # Leitura do valor da temperatura (MAX6675)
        tempCelsius = instrument.read_register(REG_TEMP, 0) / 1000.0  # Registrador 104 (Temperatura)

        # Exibe os valores lidos
        print(f"Valor A0: {dataA0}")
        print(f"Valor A1: {dataA1}")
        print(f"Valor A2: {dataA2}")
        print(f"Valor A3: {dataA3}")
        print(f"Temperatura (Celsius): {tempCelsius}")

    except minimalmodbus.NoResponseError:
        print("Erro: Nenhuma resposta do escravo.")
    except minimalmodbus.InvalidResponseError:
        print("Erro: Resposta inválida do escravo.")
    except Exception as e:
        print(f"Erro de comunicação Modbus: {e}")

if __name__ == "__main__":
    while True:
        ler_dados_modbus()
