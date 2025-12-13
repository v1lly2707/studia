function [A,b,U,T,w,x,r_norm,iteration_count] = solve_Gauss_Seidel()
% A - macierz z równania macierzowego A * x = b
% b - wektor prawej strony równania macierzowego A * x = b
% U - macierz trójkątna górna, która zawiera wszystkie elementy macierzy A powyżej głównej diagonalnej,
% T - macierz trójkątna dolna równa A-U
% w - wektor pomocniczy opisany w instrukcji do Laboratorium 3
%       – sprawdź wzór (7) w instrukcji, który definiuje w jako w_{GS}.
% x - rozwiązanie równania macierzowego
% r_norm - wektor norm residuum kolejnych przybliżeń rozwiązania; norm(A*x-b);
% iteration_count - liczba iteracji wymagana do wyznaczenia rozwiązania
%       metodą Gaussa-Seidla

% losowanie rozmiaru macierzy
N = randi([5000, 8000]);

% generowanie macierzy A i wektora B
[A, b] = generate_matrix(N);


D = diag(diag(A));  % macierz diagonalna
L = tril(A, -1);    % macierz dolna
U = triu(A, 1);     % macierz gorna

% T=D+L
T = D + L;            % acierz do rozwiązania układu w iteracji
w = T \ b;            % w = (D+L)^(-1) * b


x = ones(N, 1);       % poczatkowe przyblizenie - same jedynki
r_norm = norm(A*x - b); % poczatkowa norma residuum
iteration_count = 0;   % licznik iteracji

% Gauss-Seidel
while r_norm(end) > 1e-12 && iteration_count < 1000
    x = T \ (b - U*x);  % rozwiazanie ukladu
    r_norm = [r_norm, norm(A*x - b)];  % norma residuum
    iteration_count = iteration_count + 1;
end

% wykres
figure;
semilogy(0:iteration_count, r_norm, 'r-o');
xlabel('Liczba iteracji');
ylabel('Norma residuum');
title('Zbieżność metody Gaussa-Seidla');
grid on;

end
