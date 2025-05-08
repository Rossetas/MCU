import serial
import csv
import time
from datetime import datetime

# Configuracion del puerto serial
SERIAL_PORT = '/tmp/ttyS1'
BAUD_RATE = 9600

# Archivo CSV donde se guardan los datos
CSV_FILENAME = 'log.csv'

def main():
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"Conectado al puerto serial {SERIAL_PORT}")

        # Esperar
        time.sleep(2)

        with open(CSV_FILENAME, mode='w', newline='') as file:
            writer = csv.writer(file)
            # Encabezados
            writer.writerow(['Timestamp', 'Modo', 'V1', 'V2', 'V3', 'V4'])

            while True:
                # Leer modo
                mode = ser.readline().decode().strip()
                if mode.startswith("MODO"):
                    # Leer los siguientes 4 voltajes
                    voltages = []
                    for _ in range(4):
                        line = ser.readline().decode().strip()
                        try:
                            volt = float(line)
                        except ValueError:
                            volt = None
                        voltages.append(volt)

                    # Registrar con timestamp
                    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                    writer.writerow([timestamp, mode] + voltages)
                    print(f"{timestamp} - {mode} - {voltages}")
                    
    except serial.SerialException as e:
        print(f"Error abriendo el puerto serial: {e}")
    except KeyboardInterrupt:
        print("END.")

if __name__ == "__main__":
    main()
