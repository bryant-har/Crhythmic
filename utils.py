import numpy as np
from keyboard import press, release, is_pressed, press_and_release
from time import sleep
from pyautogui import keyUp, keyDown


def get(num_samples, thresh, ser):
    xy = []
    _ = ser.read_until(b"z")
    for _ in range(num_samples):
        x = int(ser.read_until(b"x")[:-1])
        y = int(ser.read_until(b"y")[:-1])
        _ = int(ser.read_until(b"z")[:-1])
        tmp = [x, y]
        if np.linalg.norm(tmp) > thresh:
            xy.append(tmp)

    return np.average(xy, axis=0) if len(xy) > 0 else None  # motion detected


def actuate_wasd(xy):
    idx = np.argmax(abs(xy))
    if idx == 0:
        if xy[0] > 0:
            down()
        else:
            up()
    else:
        if xy[1] > 0:
            right()
        else:
            left()


def actuate_arrow(xy):
    idx = np.argmax(abs(xy))
    if idx == 0:
        if xy[0] > 0:
            downa()
        else:
            upa()
    else:
        if xy[1] > 0:
            righta()
        else:
            lefta()


def actuate_wasd(xy, last):
    idx = np.argmax(abs(xy))
    if idx == 0:
        if xy[0] > 0:
            return down(last)
        else:
            return up(last)
    else:
        if xy[1] > 0:
            return right(last)
        else:
            return left(last)


def actuate_wasd_single(xy):
    idx = np.argmax(abs(xy))
    if idx == 0:
        if xy[0] > 0:
            press_and_release("d")
        else:
            press_and_release("a")
    else:
        if xy[1] > 0:
            press_and_release("w")
        else:
            press_and_release("s")


def releaseall():
    release("w")
    release("a")
    release("s")
    release("d")


def left(lastpressed):
    if lastpressed == "d":
        releaseall()
        return ""
    elif not lastpressed == "a":
        releaseall()
        press("a")
    return "a"


def right(lastpressed):
    if lastpressed == "a":
        releaseall()
        return ""

    elif not lastpressed == "d":
        releaseall()
        press("d")
    return "d"


def up(lastpressed):
    if lastpressed == "s":
        releaseall()
        return ""

    elif not lastpressed == "w":
        releaseall()
        press("w")
    return "w"


def down(lastpressed):
    if lastpressed == "w":
        releaseall()
        return ""
    elif not lastpressed == "s":
        releaseall()
        press("s")
    return "s"


def lefta():
    if is_pressed("right arrow"):
        release("right arrow")
    else:
        press_and_release("left arrow")


def righta():
    if is_pressed("left arrow"):
        release("left arrow")
    else:
        press_and_release("right arrow")


def upa():
    if is_pressed("down arrow"):
        release("down arrow")
    else:
        press_and_release("up arrow")


def downa():
    if is_pressed("up arrow"):
        release("up arrow")
    else:
        press_and_release("down arrow")
