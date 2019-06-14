#!/usr/bin/python

# importes importante para o funcionamento do script, talvez seja necessário 
# baixar algum ou atualizar
from datetime import datetime
import serial
import time
import csv

# indica a porta serial usada e a velocidade
# ambos os atributos podem ser vistos na serial do arduino
# em SO Windows deve ser algo como "...COM4" 
ser = serial.Serial('/dev/ttyUSB0', 9600)
ser.flushInput()

# função while que irá executar até desconectar o cabo usb
while True:
    try:
        # lendo os dados da serial e passando para um vetor
        ser_bytes = ser.readline()
        decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
        dados = decoded_bytes.split(',')
        # apenas um print no shell
        print(decoded_bytes)
        # cria/abre um arquivo, nesse exemplo com um nome "datalogger.csv" 
        # com o atributo "a", significa "append", ou seja, não irá execluir o arquivo
        # e sim escrever abaixo
        with open("datalogger.csv","a") as f:
        	#designa o delimitador usado no arquivo "f" criado acima, usamos a  ","
            writer = csv.writer(f,delimiter=",")
            #escreve uma linha com os parametros passados, nesse exemplo, o timestamp 
            # e os 7 dados vindo da serial 
            writer.writerow([datetime.fromtimestamp(time.time()),
            	dados[0],dados[1],dados[2],dados[3],dados[4],dados[5],dados[6]])
    except:
        print("Keyboard Interrupt")
        break
