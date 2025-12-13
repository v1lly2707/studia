function [xvec, xdif, xsolution, ysolution, iterations] = velocity_secant()
% Wyznacza miejsce zerowe funkcji velocity_difference metodą siecznych.
% xvec - wektor z kolejnymi przybliżeniami miejsca zerowego;
% xdif - wektor różnic kolejnych przybliżeń miejsca zerowego
% xsolution - obliczone miejsce zerowe
% ysolution - wartość funkcji velocity_difference dla xsolution
% iterations - liczba iteracji potrzebna do wyznaczenia rozwiązania

x0 = 1;
x1 = 40;
ytolerance = 1e-12;
max_iterations = 1000;

f0 = velocity_difference(x0);
f1 = velocity_difference(x1);

xvec = [];
xdif = [];

for ii = 1:max_iterations
    x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
    f2 = velocity_difference(x2);

    xvec(ii,1) = x2;

    if abs(f2) < ytolerance
        xsolution = x2;
        ysolution = f2;
        iterations = ii;
        break;
    end

    x0 = x1;
    f0 = f1;
    x1 = x2;
    f1 = f2;
end

for i = 1:iterations-1
    xdif(i,1) = abs(xvec(i+1,1) - xvec(i,1));
end

figure;
subplot(2,1,1);
plot(xvec, 'o-');
title('Kolejne przybliżenia miejsca zerowego (skala liniowa)');
xlabel('Iteracja');
ylabel('x');

subplot(2,1,2);
semilogy(xdif, 's-');
title('Zmiana między kolejnymi przybliżeniami (skala logarytmiczna)');
xlabel('Iteracja');
ylabel('|x_{k+1} - x_k|');

saveas(gcf, 'zadanie6.png');
end

function velocity_delta = velocity_difference(t)
% Wyznacza prędkość rakiety po czasie t od startu pomniejszoną o wartość M.
% t - [s] czas od startu rakiety
% velocity_delta [m/s] - różnica między aktualną prędkością a 700 m/s

m0 = 150000;      
q = 2700;        
u = 2000;       
g = 1.622;       
M = 700; 

if t <= 0
    error('Przerwanie działania');
end

v = u * log(m0 / (m0 - q * t)) - g * t;

velocity_delta = v - M;

end
