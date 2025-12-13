function [A,b,x,vec_loop_times,vec_iteration_count] = benchmark_solve_Jacobi(vN)
% Pomiar wydajności metody Jacobiego dla length(vN) równań macierzowych,
% przy czym liczba zmiennych i-tego równania wynosi vN(i).
% A - tablica komórkowa zawierająca zestaw macierzy A do równania macierzowego
%       A{i}*x{i}=b{i}, gdzie size(A{i},1) = vN(i)
% b - tablica komórkowa prawych stron równań A{i}*x{i}=b{i}
% x - tablica komórkowa z rozwiązaniami równań A{i}*x{i}=b{i}
% vec_loop_times(i) - czas wyznaczenia i-tego rozwiązania metodą Jacobiego
% vec_iteration_count(i) - liczba iteracji wykonana przy wyznaczeniu
%       i-tego rozwiązania metodą Jacobiego

vec_loop_times = zeros(1,length(vN));  % czasy dzialania
vec_iteration_count = zeros(1,length(vN)); % liczba iteracji

for i = 1:length(vN)
    N = vN(i);  
    [A{i},b{i}] = generate_matrix(N);  
    x{i} = ones(N,1);  % na poczatku wektor same 1

    % macierze M i w
    D = diag(diag(A{i}));   % macierz diagonalna
    L = tril(A{i}, -1);     % macierz dolna
    U = triu(A{i}, 1);      % macierz gorna

    
    M = -D \ (L + U);  
    w = D \ b{i};  

    % jacobi iteracyjnie
    iteration_count = 0;
    inorm = norm(A{i} * x{i} - b{i});  % poczatkowa norma residuum

    tic  % start pomiaru
    while inorm > 1e-12 && iteration_count < 1000
        x{i} = M * x{i} + w;  % przyblizenia rozwiazania
        inorm = norm(A{i} * x{i} - b{i});  % norma residuum
        iteration_count = iteration_count + 1;
    end
    vec_loop_times(i) = toc;  % koniec pomiaru 
    vec_iteration_count(i) = iteration_count;  
end



figure;

% wykres gorny
subplot(2,1,1);
plot(vN, vec_loop_times, '-o', 'LineWidth', 2);
xlabel('Rozmiar macierzy N');
ylabel('Czas obliczeń [s]');
title('Zależność czasu obliczeń od rozmiaru macierzy');
grid on;

% wykres dolny
subplot(2,1,2);
plot(vN, vec_iteration_count, '-s', 'LineWidth', 2);
xlabel('Rozmiar macierzy N');
ylabel('Liczba iteracji');
title('Liczba iteracji w zależności od rozmiaru macierzy');
grid on;

end
