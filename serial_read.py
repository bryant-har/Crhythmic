import serial
from time import sleep
import utils


def loop(port):
    with serial.Serial(port, 115200, timeout=1) as ser:
        while ser.is_open:
            ser.reset_input_buffer()
            # sometimes hallucinates big motions so make threshold > 4000 usu
            vec = utils.get(50, 1000, ser)
            if vec is not None:
                utils.actuate_wasd(vec)
                sleep(0.1)
                ser.reset_input_buffer()


if __name__ == "__main__":
    loop("/dev/tty.usbmodemSDA41E9CE1B1")
