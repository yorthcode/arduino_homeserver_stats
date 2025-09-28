import psutil, serial, time, subprocess, serial.tools.list_ports

PORT = "/dev/ttyUSB0"
BAUD = 9600

def get_temp():
    try:
        sensors_output = subprocess.check_output(["sensors"]).decode()
        for line in sensors_output.splitlines():
            if "Package id 0:" in line:
                return int(float(line.split("+")[1].split("°")[0]))
        return 0
    except:
        return 0

def open_serial():
    while True:
        try:
            ser = serial.Serial(PORT, BAUD, timeout=3)
            time.sleep(3)
            return ser
        except serial.SerialException as e:
            time.sleep(5)

def main():
    ser = open_serial()
    while True:
        try:
            cpu = int(psutil.cpu_percent(interval=1))
            ram = int(psutil.virtual_memory().percent)
            temp = get_temp()
            msg = f"{cpu},{ram},{temp}\n"

            ser.write(msg.encode())
            ser.flush()

        except (serial.SerialException, OSError) as e:
            ser.close()
            ser = open_serial()

if __name__ == "__main__":
    main()
