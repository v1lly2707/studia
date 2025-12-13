function [A, b, x, vec_time_direct] = benchmark_solve_direct(vN)
% Pomiar czasu rozwiązania length(vN) równań macierowych metodą LU,
% przy czym liczba zmiennych i-tego równania wynosi vN(i).
% A - tablica komórkowa zawierająca zestaw macierzy A do równania macierzowego
%       A{i}*x{i}=b{i}, gdzie size(A{i},1) = vN(i)
% b - tablica komórkowa prawych stron równań A{i}*x{i}=b{i}
% x - tablica komórkowa z rozwiązaniami równań A{i}*x{i}=b{i}
% vec_time_direct(i) - czas wyznaczenia i-tego rozwiązania metodą LU

% tablice
A = cell(1, length(vN));
b = cell(1, length(vN));
x = cell(1, length(vN));
vec_time_direct = zeros(1, length(vN));

for i = 1:length(vN)
    N = vN(i); % rozmiar macierzy

    % generowanie macierzy A i wektora B
    [A{i}, b{i}] = generate_matrix(N);

    % metoda LU
    tic;
    [L, U, P] = lu(A{i});
    y = L \ (P * b{i}); % podstawienie w przod
    x{i} = U \ y;       % podstawienie wstecz
    vec_time_direct(i) = toc; % zapisanie czasu
end

% tworzenie wykresu
figure;
plot(vN, vec_time_direct, '-o', 'LineWidth', 2, 'MarkerSize', 8);
xlabel('Rozmiar macierzy N');
ylabel('Czas obliczeń [s]');
title('Zależność czasu obliczeń od rozmiaru macierzy');
grid on;

end
