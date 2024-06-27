import minimalmodbus
import time

# Configurar o dispositivo Modbus
instrument = minimalmodbus.Instrument('/dev/ttyUSB0', 1)  # Porta e ID do escravo
instrument.serial.baudrate = 9600
instrument.serial.bytesize = 8
instrument.serial.parity   = minimalmodbus.serial.PARITY_NONE
instrument.serial.stopbits = 1
instrument.serial.timeout  = 1  # Tempo de timeout em segundos

# Funcao para ler e imprimir os valores
def read_and_print():
    try:
        adc0 = instrument.read_register(0, 0)  # Ler registrador 0
        adc1 = instrument.read_register(1, 0)  # Ler registrador 1
        adc2 = instrument.read_register(2, 0)  # Ler registrador 2
        adc3 = instrument.read_register(3, 0)  # Ler registrador 3

        print(f'ADC0: {adc0}')
        print(f'ADC1: {adc1}')
        print(f'ADC2: {adc2}')
        print(f'ADC3: {adc3}')

    except IOError:
        print("Falha na leitura do dispositivo")

while True:
    read_and_print()
    time.sleep(1)  # Esperar 1 segundo antes de ler novamente
