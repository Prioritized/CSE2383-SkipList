"""
script.py

author:  Jack Fletcher
created: 12/14/2016
updated: 12/18/2016

Analysis script for timing results from data structures.
See /C++/ for data source.
"""
import os
import numpy as np
import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt


def plot(structure_, type_):
    if type_ == "linear":
        return plot_linear(structure_)
    else:
        return plot_log(structure_)

def plot_log(struct):
    fig, axes = plt.subplots(1, len(df.operation.unique()), sharex = 'row', sharey = 'row', figsize = (9, 3))
    fig.suptitle(struct.title() + " Logarithmic", size = 16)

    for j, op in enumerate(df.operation.unique()):
        axes[j].scatter(x = 'n', y = 'tpo', data = df[(df.structure == struct) & (df.operation == op)],
                        color = colors[j], s = 5)
        axes[j].set_xscale('log')

        # adjust axes
        buffer = 0.05

        max_y = df[df.structure == struct]['tpo'].max()
        lower_y = -buffer * np.ceil(max_y)
        upper_y = (1 + buffer) * np.ceil(max_y)

        max_x = df[df.structure == struct]['n'].max()
        upper_x = 10 ** (np.ceil(np.log10(max_x) + 0.5) - 0.1)

        axes[j].set_xlim((10 ** -0.5, upper_x))
        axes[j].set_ylim((lower_y, upper_y))

        axes[j].yaxis.major.formatter._useMathText = True
        axes[j].yaxis.get_major_formatter().set_powerlimits((0, 1))
        axes[j].yaxis.set_major_locator(mpl.ticker.MaxNLocator(integer = True))

        axes[j].grid(which = 'minor', linewidth = 0.5)
        axes[j].grid(which = 'major', linewidth = 1)
        axes[j].tick_params(axis = 'x', which = 'minor')

    # set axis labels and remove ticks on top and right sides of the plot
    axes[0].set_ylabel(r"Time per Operation ($\mu$s)")
    fig.canvas.draw()
    for i, axis in enumerate(axes):
        axis.set_xlabel("n")
        axis.xaxis.set_ticks_position('bottom')
        if i == 0:
            axis.yaxis.set_ticks_position('left')
        else:
            axis.yaxis.set_ticks_position('none')

    # set operation labels
    pad = 2
    for ax, col in zip(axes, cols):
        ax.annotate(col, xy = (0.5, 1), xytext = (0, pad),
                    xycoords = 'axes fraction', textcoords = 'offset points',
                    size = 'large', ha = 'center', va = 'baseline')

    plt.tight_layout()
    plt.subplots_adjust(top = 0.85, wspace = 0.05)
    fig.savefig(results_dir + '{}_log.png'.format(struct.replace(" ", "")), dpi = 100)
    return

def plot_linear(struct):
    fig, axes = plt.subplots(1, len(df.operation.unique()), sharex = 'row', sharey = 'row', figsize = (9, 3))
    fig.suptitle(struct.title() + " Linear", size = 16)

    for j, op in enumerate(df.operation.unique()):
        axes[j].scatter(x = 'n', y = 'tpo', data = df[(df.structure == struct) & (df.operation == op)],
                        color = colors[j], s = 5)

        buffer = 0.05

        max_x = df[df.structure == struct]['n'].max()
        max_y = df[df.structure == struct]['tpo'].max()

        lower_x = -buffer * (10 ** np.ceil(np.log10(max_x)))
        upper_x = (1 + buffer) * (10 ** np.ceil(np.log10(max_x)))

        lower_y = -buffer * np.ceil(max_y)
        upper_y = (1 + buffer) * np.ceil(max_y)

        axes[j].set_xlim((lower_x, upper_x))
        axes[j].set_ylim((lower_y, upper_y))

        fig.canvas.draw()
        axes[j].xaxis.major.formatter._useMathText = True
        axes[j].yaxis.major.formatter._useMathText = True

        axes[j].xaxis.get_major_formatter().set_powerlimits((0, 1))
        axes[j].yaxis.get_major_formatter().set_powerlimits((0, 1))

        axes[j].xaxis.set_major_locator(mpl.ticker.MaxNLocator(integer = True))
        axes[j].yaxis.set_major_locator(mpl.ticker.MaxNLocator(integer = True))

        # axes[j].yaxis.set_minor_locator(mpl.ticker.AutoMinorLocator(2))
        # axes[j].xaxis.set_minor_locator(mpl.ticker.AutoMinorLocator(2))
        # axes[j].grid(b = True, which = 'minor', linewidth = 0.5)

        # axes[j].set_axis_bgcolor("silver")

    # set axis labels and remove ticks on top and right sides of the plot
    axes[0].set_ylabel(r"Time per Operation ($\mu$s)")
    for i, axis in enumerate(axes):
        axis.set_xlabel("n")
        axis.xaxis.set_ticks_position('bottom')
        if i == 0:
            axis.yaxis.set_ticks_position('left')
        else:
            axis.yaxis.set_ticks_position('none')

    # set operation labels
    pad = 2
    for ax, col in zip(axes, cols):
        ax.annotate(col, xy = (0.5, 1), xytext = (0, pad),
                    xycoords = 'axes fraction', textcoords = 'offset points',
                    size = 'large', ha = 'center', va = 'baseline')

    plt.tight_layout()
    plt.subplots_adjust(top = 0.85, wspace = 0.05)
    fig.savefig(results_dir + '{}_linear.png'.format(struct.replace(" ", "")), dpi = 100)

def make_results_dir():
    script_dir = os.path.dirname(__file__)
    results_dir = os.path.join(script_dir, 'plots/')

    if not os.path.isdir(results_dir):
        os.makedirs(results_dir)

    return results_dir

if __name__ == '__main__':
    mpl.style.use('ggplot')

    df = pd.read_csv('../data/timing_results.csv')

    max_input_size = {"skip list": 10000000,
                      "binary tree": 10000000,
                      "linked list": 100000}

    colors = ['#F8766D', '#00BA38', '#619CFF']

    rows = [struct for struct in df.structure.unique()]
    cols = [op for op in df.operation.unique()]

    while True:
        choice1 = input("\nMain Menu:\n(1) Skip List\n(2) Binary Search Tree\n(3) Linked List\n(7) All\n(9) Exit\n")
        map_choice1 = {1: "skip list", 2: "binary tree", 3: "linked list", 7: "all", 9: "exit"}
        try:
            choice1 = map_choice1[int(choice1)]
        except KeyError:
            print("There was an input error. Enter the number next to the selection.")
            continue

        if choice1 == "exit":
            break
        else:
            results_dir = make_results_dir()

        if choice1 == "all":
            options = [(struct, type) for struct in rows for type in ("linear", "log")]
            for struct, type in options:
                plot(struct, type)
                plt.show()
            continue

        choice2 = input("\nChoose:\n(1) Linear\n(2) Log\n(8) Back\n(9) Exit\n")
        map_choice2 = {1: "linear", 2: "log", 8: "back", 9: "exit"}
        try:
            choice2 = map_choice2[int(choice2)]
        except KeyError:
            print("There was an input error. Enter the number next to the selection.")
            continue

        if choice2 == "exit":
            break
        elif choice2 == "back":
            continue

        results_dir = make_results_dir()

        plot(choice1, choice2)
        plt.show()
