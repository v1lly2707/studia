clear all;
close all;
format compact;

% wartosci od 1000 do 8000 co 1000
vN = 1000:1000:8000;

% wywolanie funkcji
[A, b, x, vec_time_direct] = benchmark_solve_direct(vN);



% zapis do PNG
print('zadanie2.png', '-dpng');
