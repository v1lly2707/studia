from random import random
from collections import defaultdict

def genX():
    p = random()
    if p < 0.17:
        return 1
    elif p < 0.27:
        return 2
    elif p < 0.77:
        return 3
    else:
        return 4

def genY(x):
    if x == 1:
        return 3
    elif x == 2:
        return 1
    elif x == 3:
        p = random()
        if p < 0.2 / 0.5:
            return 3
        else:
            return 4
    elif x == 4:
        p = random()
        if p < 0.03 / 0.23:
            return 1
        else:
            return 2

def genPoints():
    x = genX()
    y = genY(x)
    return (x, y)

counts = defaultdict(int)
N = 100000

for _ in range(N):
    point = genPoints()
    counts[point] += 1


for point in sorted(counts.keys()):
    print(f" {point}: {counts[point]} ")
