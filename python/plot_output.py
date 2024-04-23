import matplotlib.pyplot as plt
import json
import numpy as np
from argparse import ArgumentParser

if __name__ == "__main__":
    parser = ArgumentParser()
    parser.add_argument("--title",
                        "-t",
                        required=False,
                        default="",
                        type=str,
                        help="Title of the figure")
    parser.add_argument("--file",
                        "-f",
                        required=False,
                        default="./output.json",
                        type=str,
                        help="Path of the json file to plot")
    args = parser.parse_args()
    title = args.title
    json_path = args.file
    with open(json_path, "r") as f:
        j = json.load(f)
    decks = []
    y = {}
    for d in j:
        y[d] = []
        decks.append(d)
        for i in range(14, 28):
            y[d].append(j[d][str(i)])
    fig = plt.figure(num=1)
    ax = fig.add_subplot(111)
    x = np.arange(14, 28)
    for d in decks:
        ax.plot(x, y[d], label=d, linewidth=0.8, linestyle='solid')
    ax.set_xlim(14, 27)
    ax.set_ylim(0, 1)
    ax.set_xticks(np.linspace(14, 27, 14))
    ax.set_yticks(np.linspace(0, 1, 11))
    ax.set_xticklabels([
        "2-0", "2-1", "2-2", "2-3", "2-4", "2-5", "2-6", "3-0", "3-1", "3-2",
        "3-3", "3-4", "3-5", "3-6"
    ])
    ax.set_yticklabels([
        "0%", "10%", "20%", "30%", "40%", "50%", "60%", "70%", "80%", "90%",
        "100%"
    ])

    ax.grid()
    ax.legend()
    plt.rcParams["font.sans-serif"] = "WenQuanYi Zen Hei"
    plt.title(title)
    plt.savefig("plot.png", dpi=300)

