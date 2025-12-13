function [A,b,M,w,x,r_norm,iteration_count] = solve_Jacobi()
% A - macierz z równania macierzowego A * x = b
% b - wektor prawej strony równania macierzowego A * x = b
% M - macierz iteracyjna metody Jacobiego
% w - wektor iteracyjny metody Jacobiego
% x - rozwiązanie równania macierzowego wyznaczone metodą Jacobiego
% r_norm - wektor norm residuum kolejnych przybliżeń rozwiązania
% iteration_count - liczba iteracji wymaganych do wyznaczenia rozwiązania

% losowanie rozmiaru macierzy
N = randi([5000, 8000]);

% generowanie macierzy A i wektora B
[A, b] = generate_matrix(N);

% macierze M i w
D = diag(diag(A));  % macierz diagonalna
L = tril(A, -1);    % macierz dolna
U = triu(A, 1);     % macierz gorna

M = -D \ (L + U);   % M = -D^(-1) * (L + U)
w = D \ b;          % w = D^(-1) * b


x = ones(N, 1);     % na poczatku wektor same 1
r_norm = norm(A*x - b);  % poczatkowa norma residuum
iteration_count = 0;     % iteracje

%jacobi
while r_norm(end) > 1e-12 && iteration_count < 1000
    x = M * x + w;                 % aktualizujemy x
    r_norm = [r_norm, norm(A*x - b)];  % norma residuum
    iteration_count = iteration_count + 1;
end

% tworzenie wykresu normy residuum
figure;
semilogy(0:iteration_count, r_norm, 'b-o');
xlabel('Liczba iteracji');
ylabel('Norma residuum');
title('Zbieżność metody Jacobiego');
grid on;

end
