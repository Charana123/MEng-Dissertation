import sys
import matplotlib as mpl
mpl.use('TkAgg')
import matplotlib.pyplot as plt
import numpy as np

if __name__ == "__main__":
    lines = tuple(open(sys.argv[1], 'r'))
    lines = map(lambda strr: strr.split(), lines);
    [x, y] = np.transpose(lines);
    plt.plot(x, y);
    plt.pause(10);
