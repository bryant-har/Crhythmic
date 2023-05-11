import serial
from time import sleep, time
import utils


def loop(port):
    last = ""
    with serial.Serial(port, 115200, timeout=1) as ser:
        while ser.is_open:
            ser.reset_input_buffer()
            # sometimes hallucinates big motions so make threshold > 1000 usu
            a = time()
            vec = utils.get(5, 1000, ser)  # get 5 samples
            if vec is not None:
                last = utils.actuate_wasd(vec, last)
                print("\nTime to Actuate: " + str(time() - a))
                ser.reset_input_buffer()


if __name__ == "__main__":
    loop("/dev/tty.usbmodemSDA41E9CE1B1")
