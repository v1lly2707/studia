import numpy as np
import matplotlib.pyplot as plt

from data import get_data, inspect_data, split_data

data = get_data()
inspect_data(data)

train_data, test_data = split_data(data) #podzial danych

# Simple Linear Regression
# predict MPG (y, dependent variable) using Weight (x, independent variable) using closed-form solution
# y = theta_0 + theta_1 * x - we want to find theta_0 and theta_1 parameters that minimize the prediction error

# We can calculate the error using MSE metric:
# MSE = SUM (from i=1 to n) (actual_output - predicted_output) ** 2

# get the columns
y_train = train_data['MPG'].to_numpy()
x_train = train_data['Weight'].to_numpy()

y_test = test_data['MPG'].to_numpy()
x_test = test_data['Weight'].to_numpy()

# TODO: calculate closed-form solution
theta_best = [0, 0]

m = x_train.size
x_matrix = np.concatenate((np.ones((m,1)),x_train.reshape(-1,1)),1)

y_matrix = y_train.reshape(-1,1)

theta_matrix = np.linalg.inv(x_matrix.T.dot(x_matrix)).dot(x_matrix.T).dot(y_matrix)

theta_best = theta_matrix.flatten()

print("θ (closed form)\t\t", theta_best)

# TODO: calculate error
# MSE = suma kwadratów (przewidywane wartości - rzeczywiste) / ilość elementów
mse = np.mean(((theta_best[0] + theta_best[1] *  x_test) - y_test) ** 2)

print("MSE (closed form)\t", mse)




# plot the regression line
x = np.linspace(min(x_test), max(x_test), 100)
y = float(theta_best[0]) + float(theta_best[1]) * x
plt.plot(x, y)
plt.scatter(x_test, y_test)
plt.xlabel('Weight')
plt.ylabel('MPG')
plt.show()

print()
# TODO: standardization
# zmiennych zależnych i niezależnych
# z = (x - μ) / σ
# populacja to zbior wszystkich wartosci wybranej cechy w naszym zbiorze treningowym
#chcemy aby odchylenie standardowe wynosilo 1 a srednia 0
x_mean = np.mean(x_train)
x_std = np.std(x_train)
y_mean = np.mean(y_train)
y_std = np.std(y_train)

x_train = (x_train - x_mean) / x_std
y_train = (y_train - y_mean) / y_std


x_matrix = np.concatenate((np.ones((m,1)),x_train.reshape(-1,1)),1)
y_matrix = y_train.reshape(-1,1)




# TODO: calculate theta using Batch Gradient Descent

theta_best = np.random.rand(1,2).reshape(-1,1)
learning_rate = 0.01 #wspolczynnik uczenia okreslajacy tempo dokonywanych zmian
epoch = 1000

for i in range(epoch):
    gradientMse = (2 / m) * x_matrix.T.dot(x_matrix.dot(theta_best) - y_matrix)
    theta_best = theta_best - learning_rate * gradientMse #aktualizacja wag

theta_best = theta_best.flatten()
print("θ (∇)\t\t\t", theta_best)


# TODO: calculate error # blad srednio-kwadratowy

x_standarized = (x_test - x_mean) / x_std

y_results = theta_best[0] + theta_best[1] * x_standarized #przewidywane wartosci

y_pred = (y_results * y_std) + y_mean

mse = np.mean((y_pred - y_test) ** 2)
print("MSE (∇)\t\t\t", mse)

# plot the regression line
x = np.linspace(min(x_test), max(x_test), 100)
x_standarized = (x - x_mean) / x_std
y_standarized = float(theta_best[0]) + float(theta_best[1]) * x_standarized

y = (y_standarized * y_std) + y_mean

plt.plot(x, y)
plt.scatter(x_test, y_test)
plt.xlabel('Weight')
plt.ylabel('MPG')
plt.show()