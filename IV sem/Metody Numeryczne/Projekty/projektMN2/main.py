import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import pickle
import os
from solve import GaussSeidel, Jacobi, LU
from genMatrix import Matrix2, VectorB
from math import sin


index = 197725
e = 7
f = 7

a1 = 5 + e
a2 = -1
a3 = -1

function = "n"
#1
A = Matrix2(a1, a2, a3)
b = VectorB( function = function)


#2

jacobi = Jacobi(A, b)
print("Wykonanie metody Jacobiego")
print(f"Czas:  {jacobi.duration}")
print(f"Błąd: {jacobi.errors[-1]}")
print(f"Iteracje:  {len(jacobi.errors)}")



gaussSeidel = GaussSeidel(A, b)
print("Wykonanie metody Gaussa-Seidela")
print(f"Czas:  {gaussSeidel.duration}")
print(f"Błąd:  {gaussSeidel.errors[-1]}") 
print(f"Iteracje:  {len(gaussSeidel.errors)}")


plt.figure()
plt.title("Norma residuum metodą Gaussa-Seidela")
plt.plot(gaussSeidel.errors, label="Gauss-Seidel")
plt.yscale('log')
plt.legend()
plt.ylabel("Norma wektora residuum")
plt.xlabel("Nr iteracji")
plt.savefig("B_gauss_seidel.png")
plt.close()

plt.figure()
plt.title("Norma residuum metodą Jacobiego")
plt.plot(jacobi.errors, label="Jacobi")
plt.yscale('log')
plt.legend()
plt.ylabel("Norma wektora residuum")
plt.xlabel("Nr iteracji")
plt.savefig("B_jacobi.png")
plt.close()


#3
a1 = 3
a2 = -1
a3 = -1

A = Matrix2(a1, a2, a3)
b = VectorB(function = function)

jacobi = Jacobi(A, b)
print("Wykonanie metody Jacobiego")
print(f"Czas:  {jacobi.duration}")
print(f"Błąd: {jacobi.errors[-1]}")
print(f"Iteracje:  {len(jacobi.errors)}")


gaussSeidel = GaussSeidel(A, b)
print("Wykonanie metody Gaussa-Seidela")
print(f"Czas:  {gaussSeidel.duration}")
print(f"Błąd:  {gaussSeidel.errors[-1]}")
print(f"Iteracje:  {len(gaussSeidel.errors)}")

plt.figure()
plt.title("Norma residuum metodą Gaussa-Seidela")
plt.plot(gaussSeidel.errors, label="Gauss-Seidel")
plt.yscale('log')
plt.legend()
plt.ylabel("Norma wektora residuum")
plt.xlabel("Nr iteracji")
plt.savefig("C_gauss_seidel.png")
plt.close()

plt.figure()
plt.title("Norma residuum metodą Jacobiego")
plt.plot(jacobi.errors, label="Jacobi")
plt.yscale('log')
plt.legend()
plt.ylabel("Norma wektora residuum")
plt.xlabel("Nr iteracji")
plt.savefig("C_jacobi.png")
plt.close()


#4
A = Matrix2(a1, a2, a3)
b = VectorB(function = function)

lu = LU(A, b)
print("Wykonanie metody LU")
print(f"Czas:  {lu.duration}")
print(f"Błąd:  {lu.errors}")



#5

a1 = 5 + e
a2 = -1
a3 = -1

size = [100, 500, 1000, 2000, 3000, 4000]

timesJacobi = []
timesGaussSeidel = []
timesLU = []

for i in size:
    A = Matrix2(a1, a2, a3, n = i)
    b = VectorB(function = function, n = i)

    jacobi = Jacobi(A, b)
    print("Wykonanie metody Jacobiego")
    print(f"Czas:  {jacobi.duration}")
    print(f"Błąd: {jacobi.errors[-1]}")
    print(f"Iteracje:  {len(jacobi.errors)}")
    timesJacobi.append(jacobi.duration)

    gaussSeidel = GaussSeidel(A, b)
    print("Wykonanie metody Gaussa-Seidela")
    print(f"Czas:  {gaussSeidel.duration}")
    print(f"Błąd:  {gaussSeidel.errors[-1]}")
    print(f"Iteracje:  {len(gaussSeidel.errors)}")
    timesGaussSeidel.append(gaussSeidel.duration)


    lu = LU(A, b)
    print("Wykonanie metody LU")
    print(f"Czas:  {lu.duration}")
    print(f"Błąd:  {lu.errors[-1]}")
    timesLU.append(lu.duration)

plt.figure()
plt.title("Czas wykonania metody Jacobiego (skala liniowa)")
plt.plot(size, timesJacobi, label="Jacobi")
plt.legend()
plt.ylabel("Czas [s]")
plt.xlabel("Rozmiar macierzy")
plt.grid(True)
plt.savefig("czas_jacobi_liniowy.png")

plt.figure()
plt.title("Czas wykonania metody Jacobiego (skala logarytmiczna)")
plt.plot(size, timesJacobi, label="Jacobi")
plt.yscale("log")
plt.legend()
plt.ylabel("Czas [s]")
plt.xlabel("Rozmiar macierzy")
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.savefig("czas_jacobi_logarytmiczny.png")

plt.figure()
plt.title("Czas wykonania metody Gaussa-Seidela (skala liniowa)")
plt.plot(size, timesGaussSeidel, label="Gauss-Seidel")
plt.legend()
plt.ylabel("Czas [s]")
plt.xlabel("Rozmiar macierzy")
plt.grid(True)
plt.savefig("czas_gauss_seidel_liniowy.png")

plt.figure()
plt.title("Czas wykonania metody Gaussa-Seidela (skala logarytmiczna)")
plt.plot(size, timesGaussSeidel, label="Gauss-Seidel")
plt.yscale("log")
plt.legend()
plt.ylabel("Czas [s]")
plt.xlabel("Rozmiar macierzy")
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.savefig("czas_gauss_seidel_logarytmiczny.png")

plt.figure()
plt.title("Czas wykonania metody LU (skala liniowa)")
plt.plot(size, timesLU, label="LU")
plt.legend()
plt.ylabel("Czas [s]")
plt.xlabel("Rozmiar macierzy")
plt.grid(True)
plt.savefig("czas_lu_liniowy.png")

plt.figure()
plt.title("Czas wykonania metody LU (skala logarytmiczna)")
plt.plot(size, timesLU, label="LU")
plt.yscale("log")
plt.legend()
plt.ylabel("Czas [s]")
plt.xlabel("Rozmiar macierzy")
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.savefig("czas_lu_logarytmiczny.png")

