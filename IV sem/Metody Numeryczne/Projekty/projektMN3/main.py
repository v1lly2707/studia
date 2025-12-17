import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
from pathlib import Path

DATAFILE = 'SpacerniakGdansk.csv'
DATADIR = Path('./2018_paths')
ADIR = Path('./assets')

def loadData():
    datafile = DATADIR / DATAFILE
    try:
        data = pd.read_csv(datafile, dtype={'Dystans (m)': np.float64, 'Wysokość (m)': np.float64})
        data = data.rename(columns={'Dystans (m)': 'x', 'Wysokość (m)': 'y'})
        if 'x' not in data.columns or 'y' not in data.columns:
            data = pd.read_csv(datafile, header=None, names=['x', 'y'])
    except Exception:
        data = pd.read_csv(datafile, header=None, names=['x', 'y'])
    return data

data = loadData()
#print(data.columns)  
data.head()

def showPlots(data: pd.DataFrame):
    plt.figure(figsize=(10, 6))
    plt.plot(data['x'], data['y'], 'o', markersize=2)
    plt.title(f'Profil wysokosciowy {DATAFILE}')
    plt.xlabel('Dystans [m]')
    plt.ylabel('Wysokosc [m]')
    plt.grid()
    ADIR.mkdir(parents=True, exist_ok=True)
    plt.savefig(ADIR / f'{DATAFILE}.png')
    plt.show()

showPlots(data)

N = 50

def fi(i: int, x: np.ndarray, point: float) -> float:
    xAux = np.ma.array(x, mask = False)
    xAux.mask[i] = True
    return np.prod((point - xAux) / (x[i] - xAux)) 

def lagrange(x: np.ndarray, y: np.ndarray, point: float) -> float:
    return np.sum([y[i] * fi(i, x, point) for i in range(len(x))])


def lagrangePoints(x: np.ndarray, y: np.ndarray, points: np.ndarray) -> np.ndarray:
    return np.array([lagrange(x, y, point) for point in points])


def showLagrange(data: pd.DataFrame, N: int):
    node = len(data) // N
    x = data['x'].values[::node]
    y = data['y'].values[::node]

    interpolated = lagrangePoints(x, y, data['x'])

    plt.figure(figsize=(10, 6))
    plt.plot(data['x'], data['y'], 'o', markersize=2, label='Oryginale punkty')
    plt.plot(data['x'], interpolated, label='Interpolacja Lagrange')
    plt.plot(x,y,'.', label = 'Wezly')
    plt.title(f'Interpolacja Lagrange {N} wezlow {DATAFILE}')
    plt.xlabel('Dystans [m]')
    plt.ylabel('Wysokosc [m]')
    plt.legend()
    plt.grid()
    plt.yscale('symlog')
    ADIR.mkdir(parents=True, exist_ok=True)
    plt.savefig(ADIR / f'{DATAFILE}_{N}_lagrange.png')
    plt.show()

showLagrange(data, N)

N = 50

def chebyshev(a: float, b: float, n: int) -> np.ndarray:
    base_nodes = 0.5 * (1 - np.cos(np.linspace(0, np.pi, n)))
    return a + (b - a) * base_nodes

def val(x: np.ndarray, y: np.ndarray, points: np.ndarray) -> np.ndarray:
    return np.array(y[np.searchsorted(x, points)]).copy()


def showChebyshev(data: pd.DataFrame, N: int):
    node = chebyshev(data['x'].values[0], data['x'].values[-1], N)
    values = val(data['x'].array, data['y'].array, node)

    X = np.linspace(data['x'].values[0], data['x'].values[-1], 1000)
    interpolated = lagrangePoints(node, values, X)

    plt.figure(figsize=(10, 6))
    plt.plot(data['x'], data['y'], 'o', markersize=2, label='Oryginale punkty')
    plt.plot(X, interpolated, label='Interpolacja Chebysheva')
    plt.plot(node, values, '.', label='Wezly')
    plt.title(f'Interpolacja Chebysheva {N} wezlow {DATAFILE}')
    plt.xlabel('Dystans [m]')
    plt.ylabel('Wysokosc [m]')
    plt.legend()
    plt.grid()
    plt.yscale('symlog')
    ADIR.mkdir(parents=True, exist_ok=True)
    plt.savefig(ADIR / f'{DATAFILE}_{N}_chebyshev.png')
    plt.show()

showChebyshev(data, N)


N = 256

def solveM(x: np.ndarray, y: np.ndarray) -> np.ndarray:
    n = len(x) - 1
    A = np.zeros((4*n, 4*n), dtype=np.float64)
    val = np.zeros(4*n, dtype=np.float64)
    val[::4] = y[:-1]
    val[1::4] = y[1:]

    for i in range(n):
        h = x[i+1] - x[i]
        idx = 4 * i  

        A[idx, idx] = 1 
        A[idx + 1, idx:idx + 4] = [1, h, h**2, h**3]  

        if i < n - 1:
            next_idx = idx + 4

            A[idx + 2, idx + 1] = 1       
            A[idx + 2, idx + 2] = 2 * h   
            A[idx + 2, idx + 3] = 3 * h**2 
            A[idx + 2, next_idx + 1] = -1  

            A[idx + 3, idx + 2] = 2        
            A[idx + 3, idx + 3] = 6 * h    
            A[idx + 3, next_idx + 2] = -2  

    A[-2, 2] = 1  
    A[-1, -2] = 2
    A[-1, -1] = 6 * (x[-1] - x[-2]) 

    return np.linalg.solve(A, val).flatten()



def spline(x: np.ndarray, y: np.ndarray, points: np.ndarray) -> np.ndarray:
    coeffs = solveM(x, y)
    result = np.empty_like(points)

    segment = 0

    for i, pt in enumerate(points):
        while segment < len(x) - 2 and not (x[segment] <= pt <= x[segment + 1]):
            segment += 1

        dx = pt - x[segment]
        a, b, c, d = coeffs[4*segment : 4*segment + 4]

        result[i] = a + b * dx + c * dx**2 + d * dx**3

    return result

def showSpline(data: pd.DataFrame, N: int):

    node = len(data) // N
    x = data['x'].values[::node]
    y = data['y'].values[::node]

    interpolated = spline(x, y, data['x'])

    plt.figure(figsize=(10, 6))
    plt.plot(data['x'], data['y'], 'o', markersize=2, label='Oryginale punkty')
    plt.plot(data['x'], interpolated, label='Interpolowane punkty')
    plt.plot(x, y, '.', label='Wezly')
    plt.title(f'Interpolacja funkcjami sklejanymi {N} wezlow {DATAFILE}')
    plt.xlabel('Dystans [m]')
    plt.ylabel('Wysokosc [m]')
    plt.legend()
    plt.grid()
    plt.yscale('symlog')
    ADIR.mkdir(parents=True, exist_ok=True)
    plt.savefig(ADIR / f'{DATAFILE}_{N}_spline.png')
    plt.show()

showSpline(data, N)


nodes = [4, 8, 16, 32, 64, 128]

def showAll():
    data = loadData()
    showPlots(data)

    for i in nodes:
        showLagrange(data, i)
        showChebyshev(data, i)
        showSpline(data, i)


DATAFILE = 'SpacerniakGdansk.csv'
showAll()

DATAFILE = 'Hel_yeah.csv'
showAll()

DATAFILE = 'MountEverest.csv'
showAll()



