#!/usr/bin/env python3
import minimalmodbus
import serial
import time
import psycopg2  # Biblioteca para conectar com PostgreSQL

# Configuração da conexão com o banco de dados PostgreSQL
def conectar_banco():
    try:
        # Conecte-se ao banco de dados PostgreSQL
        conn = psycopg2.connect(
            host="localhost",  # Endereço do banco de dados
            database="grafana",  # Nome do banco de dados
            user="postgres",  # Usuário do banco de dados
            password="SenhaPostgres@2024!"  # Senha do banco de dados
        )
        return conn
    except Exception as e:
        print(f"Erro ao conectar ao banco de dados: {e}")
        return None

# Função para inserir dados no banco de dados
def inserir_dados(conn, corrente, tensao, vibracao, temperatura):
    try:
        # Cria um cursor para executar comandos SQL
        cur = conn.cursor()

        # Query SQL para inserir os dados na tabela
        sql = """
        INSERT INTO public.dados_sensores_auto (data, "Corrente (A)", "Tensao (V)", "Vibracao", "Temperatura (C)")
        VALUES (%s, %s, %s, %s, %s);
        """

        # Executa a query passando os valores dos registradores
        cur.execute(sql, (corrente, tensao, vibracao, temperatura))

        # Confirma as mudanças no banco
        conn.commit()

        # Fecha o cursor
        cur.close()

        print("Dados inseridos no banco de dados com sucesso.")

    except Exception as e:
        print(f"Erro ao inserir dados no banco de dados: {e}")

# Solicita ao usuário o ID do escravo e o valor do registrador
id_modbus = 1
conn = conectar_banco()  # Conecta ao banco de dados

if conn is None:
    print("Falha ao conectar ao banco de dados. Encerrando o programa.")
else:
    while True:
        # Leitura dos registradores
        registrador_0 = 0  # Corrente
        registrador_1 = 1  # Tensão
        registrador_2 = 2  # Vibração
        registrador_3 = 3  # Outro registrador, mas não será usado no banco
        registrador_4 = 4  # Temperatura
        numero_decimais = 2  # Número de casas decimais esperadas no valor

        try:
            # Define parâmetros para a comunicação (Porta Serial, ID do escravo)
            instrument = minimalmodbus.Instrument('COM6', id_modbus)
            instrument.serial.baudrate = 9600  # Configura o baudrate se necessário
            instrument.serial.bytesize = 8
            instrument.serial.parity = serial.PARITY_NONE
            instrument.serial.stopbits = 1
            instrument.serial.timeout = 1  # Timeout em segundos

            # Lê os valores dos registradores
            valor_registrador_0 = instrument.read_register(registrador_0, numero_decimais)  # Corrente
            valor_registrador_1 = instrument.read_register(registrador_1, numero_decimais)  # Tensão
            valor_registrador_2 = instrument.read_register(registrador_2, numero_decimais)  # Vibração
            valor_registrador_4 = instrument.read_register(registrador_4, numero_decimais)  # Temperatura

            # Exibe os valores lidos
            print(f'Valor dos registradores: \n'
                  f'Corrente (A): {valor_registrador_0} \n'
                  f'Tensão (V): {valor_registrador_1} \n'
                  f'Vibração: {valor_registrador_2} \n'
                  f'Temperatura (C): {valor_registrador_4}')

            # Insere os dados no banco de dados
            inserir_dados(conn, valor_registrador_0, valor_registrador_1, valor_registrador_2, valor_registrador_4)

        except ValueError:
            print("Por favor, insira valores numéricos válidos para ID e status.")
        except minimalmodbus.NoResponseError:
            print("Nenhuma resposta do escravo. Verifique a conexão e o ID do escravo.")
        except Exception as e:
            print(f"Erro ao comunicar com o dispositivo: {e}")

        # Espera por 1 segundo antes de ler novamente
        time.sleep(1)

    # Fecha a conexão com o banco de dados após sair do loop
    conn.close()
