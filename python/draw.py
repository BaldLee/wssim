import matplotlib.pyplot as plt
import json
import numpy as np

if __name__ == "__main__":
    with open("out.json") as f:
        j = json.load(f)
    decks = ["8/25","6/25","8/30","6/30","6/20","4/20","4/15"]
    l={}
    for s in decks:
        l[s] = []
    for i in range(14, 28):
        for s in decks:
            l[s].append(j[str(i)][s])
    for s in decks:
        print(f"{s}: {l[s]}")
    fig = plt.figure(num=1)
    ax = fig.add_subplot(111)
    x = np.arange(14, 28)
    for s in decks:
        ax.plot(x, l[s], label=s)
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
    plt.show()
    plt.savefig("out.jpg")