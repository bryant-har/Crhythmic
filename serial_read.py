import serial
from time import sleep, time
import utils


def loop(port):
    with serial.Serial(port, 115200, timeout=1) as ser:
        while ser.is_open:
            ser.reset_input_buffer()
            # sometimes hallucinates big motions so make threshold > 1000 usu
            a = time()
            vec = utils.get(10, 1000, ser)  # get 10 samples
            if vec is not None:
                utils.actuate_wasd(vec)
                print("\nTime to Actuate: " + str(time() - a))
                print()
                ser.reset_input_buffer()


if __name__ == "__main__":
    loop("/dev/tty.usbmodemSDA41E9CE1B1")
