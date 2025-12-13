function [A,b,x,vec_loop_times,vec_iteration_count] = benchmark_solve_Gauss_Seidel(vN)

vec_loop_times = zeros(1,length(vN));
vec_iteration_count = zeros(1,length(vN));

for i = 1:length(vN)
    N = vN(i);

    [A{i}, b{i}] = generate_matrix(N); 
    x{i} = ones(N,1);

    iteration_count = 0;
    inorm = 1e22;  

    tic
    while (inorm > 1e-12 && iteration_count < 1000)
        x_old = x{i};

        % Gauss-Seidel
        for j = 1:N
            sum1 = A{i}(j,1:j-1) * x{i}(1:j-1);
            sum2 = A{i}(j,j+1:N) * x{i}(j+1:N);
            x{i}(j) = (b{i}(j) - sum1 - sum2) / A{i}(j,j);
        end

        % norma roznicy miedzy iteracjami
        inorm = norm(x{i} - x_old, inf);
        iteration_count = iteration_count + 1;
    end
    vec_loop_times(i) = toc;
    vec_iteration_count(i) = iteration_count;
end

figure;

% czas obliczen
subplot(2,1,1);
plot(vN, vec_loop_times, 'ro-', 'LineWidth', 2);
xlabel('Rozmiar macierzy N');
ylabel('Czas obliczeń [s]');
title('Zależność czasu obliczeń od rozmiaru macierzy');
grid on;

% liczba iteracji
subplot(2,1,2);
plot(vN, vec_iteration_count, 'bs-', 'LineWidth', 2);
xlabel('Rozmiar macierzy N');
ylabel('Liczba iteracji');
title('Liczba iteracji w zależności od rozmiaru macierzy');
grid on;


end
