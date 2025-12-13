function [xvec,xdif,xsolution,ysolution,iterations] = velocity_bisection()
% Wyznacza miejsce zerowe funkcji velocity_difference metodą bisekcji.
% xvec - wektor z kolejnymi przybliżeniami miejsca zerowego
% xdif - różnice kolejnych przybliżeń
% xsolution - miejsce zerowe
% ysolution - wartość funkcji w xsolution
% iterations - liczba iteracji

a = 1;      
b = 40;   
ytolerance = 1e-12;
max_iterations = 1000;

fa = velocity_difference(a);
fb = velocity_difference(b);

if fa * fb >= 0
    error('Brak zmiany znaku funkcji velocity_difference w przedziale [%f, %f]', a, b);
end

xvec = [];
xdif = [];

for ii = 1:max_iterations
    c = (a + b) / 2;
    xvec(ii,1) = c;
    
    fc = velocity_difference(c);
    
    if abs(fc) < ytolerance
        xsolution = c;
        ysolution = fc;
        iterations = ii;
        break;
    end
    
    if fa * fc < 0
        b = c;
        fb = fc;
    else
        a = c;
        fa = fc;
    end
end

for i = 1:iterations-1
    xdif(i,1) = abs(xvec(i+1) - xvec(i));
end

=figure

subplot(2,1,1)
plot(1:length(xvec), xvec, 'o-')
xlabel('Numer iteracji')
ylabel('Przybliżenie miejsca zerowego')
title('Kolejne przybliżenia czasu (skala liniowa)')

subplot(2,1,2)
semilogy(1:length(xdif), xdif, 'o-')
xlabel('Numer iteracji')
ylabel('|x_{n+1} - x_n|')
title('Zmiana różnicy pomiędzy kolejnymi przybliżeniami (skala logarytmiczna)')

saveas(gcf, 'zadanie5.png')

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