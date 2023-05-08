import numpy as np


def get(num_samples, thresh, ser):
    xyz = []
    for _ in range(num_samples):
        tmp = []
        while len(tmp) < 3:
            a = ser.readline()[:-1]
            if a:
                tmp.append(int(a))
            else:
                print("Invalid Byte Discarded")
                tmp = [0, 0, 0]
                break
        tmp[1] = 0  # Discard y coordinate because we don't want to break the monitor?
        tmp[2] -= 2000
        if np.linalg.norm(tmp) > thresh:
            xyz.append(tmp)

    return np.average(xyz, axis=0) if len(xyz) > 0 else None  # motion detected
