import serial
import time
ser = serial.Serial("COM6",115200,timeout=0)

file = open("archivo.csv", "a")
file.write('temperatura;humedad;latitud;longitud;altitud;fecha;hora;\n')
file.write('*C,%;*;*;m;aa/mm/dd;h:m:s;\n')
while 1:
	for a in range (0,2):
		info = ser.readline()
		info = str(info)
		b=info[2:7]
		file.write(b)
		file.write(';')
		print(info)
	file.write('\n')
	time.sleep(5)
file.close()