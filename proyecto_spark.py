import requests
import json
from datetime import date
from datetime import datetime
from pyspark.sql import SparkSession


spark = SparkSession.builder.appName('Proyecto final Almacenamiento').getOrCreate()
sc = spark.sparkContext
fecha_inicial = False
fecha_final = False

def getDate(msj):
	print(msj)
	dateInput=(raw_input("Ingresa la fecha con el siguiente formato (YYYY-MM-DD): "))
	Fecha = False
	try:
		fecha=datetime.strptime(dateInput,"%Y-%m-%d")
	except Exception as e:
		print("Algo salio mal, ingresaste valores correctos?. Error: ",e)
	return  fecha

def validateDate(f_i,f_f):
	if f_i>f_f:
		print("La fehca incial no puede ser mayor que la fecha final")
		return False
	else:
		return True

def getData():
	url = "http://144.202.34.148:3132/interruptores"
	response = requests.get(url)
	data = response.text
	parsed = json.loads(data)
	return sc.parallelize(parsed['data']['Interruptores'])



def getDataInRangeDate(x):
	global fecha_inicial
	global fecha_final
	fecha = datetime.strptime(x['fecha'], '%Y-%m-%dT%H:%M:%S.%fZ')
	if(fecha>=fecha_inicial and fecha<=fecha_final):
		print(x)

def main():
	global fecha_inicial
	global fecha_final
	print("###################################")
	print("###Proyecto FINAL ALMACENAMIENTO###")
	print("###################################")
	run = True
	while run:
		interruptores = getData()
		fecha_inicial = getDate("Fecha incial:\n")
		fecha_final = getDate("Fecha final:\n")
		if(validateDate(fecha_inicial,fecha_final)):
			interruptores.foreach(getDataInRangeDate)
		R = input("Quieres probar nuevamente?\nPulsa 1 para continuar\nPara salir pulsa cualquier otro numero\nR: ")
		if(R!=1):
			run=False

if __name__ == '__main__':
	main()

