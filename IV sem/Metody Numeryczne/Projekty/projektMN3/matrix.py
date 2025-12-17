import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numba as nb

@nb.njit

def pivot(L: np.ndarray, U: np.ndarray, P: np.ndarray, i: int) -> None:
    maxIdx = np.argmax(np.abs(U[i:, i])) + i

    if maxIdx == i:
        return
    
    for j in range(U.shape[1]):
        U[i, j], U[maxIdx, j] = U[maxIdx, j], U[i, j]
        P[i, j], P[maxIdx, j] = P[maxIdx, j], P[i, j]
        L[i, j], L[maxIdx, j] = L[maxIdx, j], L[i, j]

@nb.njit

def LU(A: np.ndarray) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
    n = A.shape[0]
    L = np.eye(n)
    U = A.copy()
    P = np.eye(n)

    for i in range(n):
        pivot(L, U, P, i)

        for j in range(i + 1, n):
            L[j, i] = U[j, i] / U[i, i]
            for k in range(i, n):
                U[j, k] -= L[j, i] * U[i, k]

    return L, U, P

@nb.njit

def solve(A: np.ndarray, b: np.ndarray) -> np.ndarray:
    L, U, P = LU(A)
    a = P @ b
    n = a.shape[0]

    for i in range(n):
        a[i] -= L[i, :i] @ a[:i]

    for i in range(n - 1, -1, -1):
        a[i] -= U[i, i + 1:] @ a[i + 1:]
        a[i] /= U[i, i]

    return a

if __name__ == "__main__":
    
    A = np.array([[3, 2, -4], [2, 3, 3], [5, -3, 1]], dtype=np.float64)
    b = np.array([3, 15, 14], dtype=np.float64)

    solution = solve(A, b)
    print("Solution:", solution)
    
    # You can also test the LU decomposition
    L, U, P = LU(A)
    print("L:\n", L)
    print("U:\n", U)
    print("P:\n", P)