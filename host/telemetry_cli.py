
def send_command(serial, cmd):
    print("send_command function called.")
    print("serial= " + serial)
    print("cmd= " + cmd)

def log_telemetry(serial, dur):
    print("log_telemetry called")
    print("serial= " + serial)
    print("dur= " + str(dur))

def main():
    print("Main Function Called")

if __name__ == '__main__':
    main()
    send_command("cereal", "eat")
    log_telemetry("surreal", 10)