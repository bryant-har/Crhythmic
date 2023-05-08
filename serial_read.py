import serial
from time import sleep
import numpy as np
import utils


def loop(port):
    with serial.Serial(port, 115200, timeout=1) as ser:
        while ser.is_open:
            ser.reset_input_buffer()
            # sometimes hallucinates big motions so make threshold > 4000 usu
            vec = utils.get(50, 4000, ser)
            if vec is not None:
                print(vec)  # max during interval
                sleep(0.1)  # delay between inputs to prevent excessive input


if __name__ == "__main__":
    loop("/dev/tty.usbmodemSDA41E9CE1B1")
