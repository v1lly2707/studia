from genMatrix import Matrix, VectorB
import copy
import numpy as np
import time
import math
import abc

class Solver(abc.ABC):
    def __init__(self, name, A, b, debug = False):
        self.name = name
        self.A = A
        self.b = b
        self.x = None
        self.debug = debug
        self.duration = 0
        self.errors = []

    def solve(self, A, b):
        pass

    def SolErr(self):
        return (self.A * self.x - self.b).norm()
    
    def __str__(self) -> str:
        return f"{self.name} duration: {self.duration}, error: {self.SolErr()}"
    



class GaussSeidel(Solver):
    def __init__(self, A, b, debug = False):
        super().__init__("Metoda Gaussa - Seidela", A, b, debug)
        self.x , self.duration, self.errors = self.solve(A, b)

    def solve(self, A, b, res = 1e-9):
        n = A.n
        x = VectorB(n, function = "1")
        xPrev = copy.deepcopy(x)
        start = time.time()
        errors = []

        for _ in range(200):
            for i in range(n):
                approx = b.matrix[i][0]
                for j in range(i):
                    approx -= A.matrix[i][j] * xPrev.matrix[j][0]
                for j in range(i + 1, n):
                    approx -= A.matrix[i][j] * x.matrix[j][0]

                xPrev.matrix[i][0] = approx / A.matrix[i][i]


            x = copy.deepcopy(xPrev)
            eq = A * x - b
            eqNorm = eq.norm()
            errors.append(eqNorm)
            if eqNorm < res:
                break

            if self.debug:
                print(f"Iteracja {_}: {eqNorm}")

        end = time.time()
        d = end - start
        return x, d, errors
    

class LU(Solver):
    def __init__(self, A, b, debug = False):
        super().__init__("Metoda LU", A, b, debug)
        self.x, self.duration, self.errors = self.solve(A, b)

    
    def solve(self, A, b):
        n = A.n
        L = Matrix(n, n)
        U = copy.deepcopy(A)


        for i in range(n):
            L.matrix[i][i] = 1
        
        y = VectorB(n, function = "1")
        x = VectorB(n, function = "1")

        start = time.time()

        for i in range(2, n+1):
            for j in range(1, i):
                L.matrix[i-1][j-1] = U.matrix[i-1][j-1] / U.matrix[j-1][j-1]
                for k in range(j, n):
                    U.matrix[i-1][k] -= L.matrix[i-1][j-1] * U.matrix[j-1][k]

        
        if self.debug:
            print("LU finished")

        
        for i in range(n):
            y.matrix[i][0] = b.matrix[i][0]
            for j in range(i):
                y.matrix[i][0] -= L.matrix[i][j] * y.matrix[j][0]

        if self.debug:
            print("Finished forward substitution")

        for i in range(n-1, -1, -1):
            x.matrix[i][0] = y.matrix[i][0]
            for j in range(i + 1, n):
                x.matrix[i][0] -= U.matrix[i][j] * x.matrix[j][0]
            x.matrix[i][0] /= U.matrix[i][i]

        if self.debug:
            print("Finished backward substitution")

        end = time.time()
        d = end - start
        error = (A *x - b).norm()

        return x, d, [error]

class Jacobi(Solver):
    def __init__(self, A, b, debug = False):
        super().__init__("Metoda Jacobiego", A, b, debug)
        self.x , self.duration, self.errors = self.solve(A, b)

    def solve(self, A, b, res = 1e-9):
        n = A.n
        x = VectorB(n, function = "1")
        xPrev = copy.deepcopy(x)
        start = time.time()
        errors = []

        for _ in range(200):
            for i in range(n):
                approx = b.matrix[i][0]
                for j in range(n):
                    if i != j:
                        approx -= A.matrix[i][j] * x.matrix[j][0]

                xPrev.matrix[i][0] = approx / A.matrix[i][i]

            x = copy.deepcopy(xPrev)
            eq = A * x - b
            eqNorm = eq.norm()
            errors.append(eqNorm)
            if eqNorm < res:
                break

            if self.debug:
                print(f"Iteracja {_}: {eqNorm}")

        end = time.time()
        d = end - start
        return x, d, errors