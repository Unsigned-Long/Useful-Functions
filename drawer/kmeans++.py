import json
import random
from matplotlib.ticker import MaxNLocator
import matplotlib.colors as mcolors
import matplotlib.pyplot as plt
import numpy as np

params_filename = '/home/csl/CppWorks/artwork/useful-funs/data/kmeans++.csv'
figure_save_filename = '/home/csl/CppWorks/artwork/useful-funs/img/kmeans++.png'

# setting
config = {
    # "text.usetex": True,
    "font.family": 'serif',  # sans-serif/serif/cursive/fantasy/monospace
    "font.size": 12,  # medium/large/small
    'font.style': 'normal',  # normal/italic/oblique
    'font.weight': 'normal',  # bold
    "mathtext.fontset": 'cm',
    "font.serif": ['cmb10'],
    "axes.unicode_minus": False,
}


def read_data(filename):
    file = open(filename, "r")
    lines = file.readlines()
    points = []
    centers = []
    count = 0
    for i in range(len(lines)):
        line = lines[i]
        if line[0] == '#':
            count += 1
            continue
        item = line.split(',')
        if count == 1:
            points.append([float(item[0]), float(item[1]), float(item[2])])
        elif count == 2:
            centers.append([float(item[0]), float(item[1]), float(item[2])])

    return (points, centers)


if __name__ == '__main__':
    plt.rcParams.update(config)
    plt.rcParams['figure.figsize'] = (15.0, 10.0)
    ax = plt.figure().add_subplot(projection='3d')

    (points, centers) = read_data(params_filename)

    ax.scatter(
        [elem[0] for elem in points], [elem[1] for elem in points], [elem[2] for elem in points], c='blue'
    )
    ax.scatter(
        [elem[0] for elem in centers], [elem[1] for elem in centers], [elem[2] for elem in centers],
        marker='X', c='red', s=100, alpha=0.5
    )
    arrow_length = 3
    line_width = 3
    ax.plot([0, arrow_length], [0, 0], [0, 0], linestyle='-', c='red', lw=line_width)
    ax.plot([0, 0], [0, arrow_length], [0, 0], linestyle='-', c='green', lw=line_width)
    ax.plot([0, 0], [0, 0], [0, arrow_length], linestyle='-', c='blue', lw=line_width)
    ax.plot([0], [0], [0], linestyle='-', c='black', lw=line_width)
    ax.set_xlim(-10, 10)
    ax.set_ylim(-10, 10)
    ax.set_zlim(-10, 10)
    ax.set_box_aspect((1, 1, 1))

    plt.tight_layout()
    plt.savefig(figure_save_filename)
    plt.show()
