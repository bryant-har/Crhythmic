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


def left():
    if is_pressed("d"):
        print("ewfew")
        releaseall()
    elif not is_pressed("a"):
        releaseall()
        press("a")


def right():
    if is_pressed("a"):
        releaseall()
    elif not is_pressed("d"):
        releaseall()
        press("d")


def up():
    if is_pressed("s"):
        releaseall()
    elif not is_pressed("w"):
        releaseall()
        press("w")


def down():
    if is_pressed("w"):
        releaseall()
    elif not is_pressed("s"):
        releaseall()
        press("s")


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
