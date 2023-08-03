import matplotlib.pyplot as plt
import json
import numpy as np

if __name__ == "__main__":
    with open("out.json") as f:
        j = json.load(f)
    l8_25 = []
    l6_25 = []
    l8_30 = []
    l6_30 = []
    for i in range(14, 28):
        l8_25.append(j[str(i)]["8/25"])
        l6_25.append(j[str(i)]["6/25"])
        l8_30.append(j[str(i)]["8/30"])
        l6_30.append(j[str(i)]["6/30"])
    fig = plt.figure(num=1)
    ax = fig.add_subplot(111)
    x = np.arange(14, 28)
    ax.plot(x, l8_25,label="8/25")
    ax.plot(x, l6_25,label="6/25")
    ax.plot(x, l8_30,label="8/30")
    ax.plot(x, l6_30,label="6/30")
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
    ax.legend()
    plt.show()
    plt.savefig("out.jpg")