from math import sin

class Matrix:

    def __init__(self, n, m):
        self.n = n
        self.m = m
        self.matrix = self.generateMatrix(n,m)

    
    def __sub__(self, other):
        out = Matrix(self.n, self.m)
        for i in range(self.n):
            for j in range(self.m):
                out.matrix[i][j] = self.matrix[i][j] - other.matrix[i][j]
        return out

    def __add__(self, other):
        out = Matrix(self.n, self.m)
        for i in range(self.n):
            for j in range(self.m):
                out.matrix[i][j] = self.matrix[i][j] + other.matrix[i][j]
        return out
    
    def mulMatrix(self, other):
        if self.m != other.n:
            raise ValueError("Matrix dimensions do not match for multiplication")
        
        out = Matrix(self.n, other.m)
        for i in range(self.n):
            for j in range(other.m):
                for k in range(self.m):
                    out.matrix[i][j] += self.matrix[i][k] * other.matrix[k][j]
        return out
    

    def mulScalar(self, scalar):
        out = Matrix(self.n, self.m)
        for i in range(self.n):
            for j in range(self.m):
                out.matrix[i][j] = self.matrix[i][j] * scalar
        return out
    
    def __mul__(self, other):
        if isinstance(other, Matrix):
            return self.mulMatrix(other)
        elif isinstance(other, (int, float)):
            return self.mulScalar(other)
        else:
            raise ValueError("Invalid operand for multiplication")
        

    def generateMatrix(self, n, m):
        matrix = []
        for i in range(n):
            row = []
            for j in range(m):
                row.append(0)
            matrix.append(row)
        return matrix
    

    def norm(self):
        out = 0
        for i in range(self.n):
            for j in range(self.m):
                out += self.matrix[i][j]**2
        return out**0.5
    
    
    
    
class Matrix2(Matrix):

    def __init__(self, a1, a2, a3, n = None, m = None):
        self.a1 = a1
        self.a2 = a2    
        self.a3 = a3

        if n is None:
            self.n = 1200 + 10 * 2 + 5

        else:
            self.n = n

        if m is None:
            self.m = self.n
        else:
            self.m = m

        self.matrix = self.generateMatrix(self.n, self.a1, self.a2, self.a3)

    def generateMatrix(self, n, a1, a2, a3):
        matrix = []
        for i in range(n):
            row = []
            for j in range(n):
                if i == j:
                    row.append(a1)
                elif i + 1 == j or i - 1 == j:
                    row.append(a2)
                elif i + 2 == j or i - 2 == j:
                    row.append(a3)
                else:
                    row.append(0)
            matrix.append(row)
        return matrix
    

class VectorB(Matrix):

    def __init__(self, n = None, function = "0"):
        self.n = n
        if self.n is None:
            self.n = 1200 + 10 * 2 + 5

        self.m = 1
        self.function = function
        self.matrix = self.generateVector(self.n, self.function)


    def generateVector(self, n, function = None):
        if function == "0":
            function = lambda x: 0
        elif function == "1":
            function = lambda x: 1
        elif function == "n":
            function = lambda n: sin(n*8) 

        vector = []
        for i in range(n):
            vector.append([function(i)])
        return vector
        

    
