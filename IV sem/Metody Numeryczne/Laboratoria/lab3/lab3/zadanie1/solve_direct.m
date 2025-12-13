function [A,b,L,U,P,y,x,r_norm,t_factorization,t_substitution,t_direct] = solve_direct()
% A, b - macierz i wektor z równania macierzowego A * x = b
% L - macierz trójkątna dolna pochodząca z wywołania [L,U,P] = lu(A);
% U - macierz trójkątna górna
% P - macierz permutacji
% y - wektor pomocniczy y=L\(P*b)
% x - wektor rozwiązania
% r_norm - norma residuum: norm(A*x-b)
% t_factorization - czas faktoryzacji macierzy A (czas działania funkcji lu)
% t_substitution - czas wyznaczenia rozwiązań równań z macierzami trójkątnymi L i U
% t_direct - czas wyznaczenia rozwiązania równania macierzowego metodą LU

% generuje rozmiar macierzy
N = randi([5000, 9000]);

% generuje macierz A i wektor B
[A, b] = generate_matrix(N);

% pomiar LU
tic;
[L, U, P] = lu(A);
t_factorization = toc;

% czas podstawien
tic;
y = L \ (P * b); % podstawienie w przod
x = U \ y;       % podstawienie wstecz
t_substitution = toc;

% ostateczny czas rozwiazania LU
t_direct = t_factorization + t_substitution;

% norma residuum
r_norm = norm(A*x - b);


% tworzenie wykresu
figure;
bar([t_direct, t_factorization, t_substitution]);
xticklabels({'t_{direct}', 't_{factorization}', 't_{substitution}'});
xlabel('Rodzaj obliczeń');
ylabel('Czas [s]');
title('Czasy obliczeń w metodzie LU');
grid on;

end