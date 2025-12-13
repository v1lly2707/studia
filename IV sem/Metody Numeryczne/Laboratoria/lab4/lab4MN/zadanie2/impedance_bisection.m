function [xvec,xdif,xsolution,ysolution,iterations] = impedance_bisection()
% Wyznacza miejsce zerowe funkcji impedance_difference metodą bisekcji.
% xvec - wektor z kolejnymi przybliżeniami miejsca zerowego
% xdif - różnice kolejnych przybliżeń
% xsolution - miejsce zerowe
% ysolution - wartość funkcji w xsolution
% iterations - liczba iteracji

a = 1; % lewa granica przedziału poszukiwań miejsca zerowego
b = 10;
ytolerance = 1e-12; % prawa granica przedziału poszukiwań miejsca zerowego
% Warunek abs(f1(xsolution))<ytolerance określa jak blisko zera ma znaleźć
% się wartość funkcji w obliczonym miejscu zerowym funkcji f1(), aby obliczenia
% zostały zakończone.
max_iterations = 1000; % maksymalna liczba iteracji wykonana przez alg. bisekcji

fa = impedance_difference(a);
fb = impedance_difference(b);

if fa * fb >= 0
    error('brak zmiany znaku funkcji w przedziale [%f, %f]', a, b);
end

xvec = [];
xdif = [];

for ii = 1:max_iterations
    c = (a + b) / 2;
    xvec(ii,1) = c; 
    
    fc = impedance_difference(c);
    
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

for i=1:iterations-1
    xdif(i,1) = abs(xvec(i+1,1)-xvec(i,1));
end


figure

subplot(2,1,1)
plot(1:length(xvec), xvec, 'o-')
xlabel('Numer iteracji')
ylabel('Przybliżenie miejsca zerowego')
title('Kolejne przybliżenia częstotliwości (skala liniowa)')

subplot(2,1,2)
semilogy(1:length(xdif), xdif, 'o-')
xlabel('Numer iteracji')
ylabel('|x_{n+1} - x_n|')
title('Zmiana różnicy pomiędzy kolejnymi przybliżeniami miejsca zerowego (skala logarytmiczna)')

saveas(gcf, 'zadanie2.png')
end

function impedance_delta = impedance_difference(f)
% Wyznacza moduł impedancji równoległego obwodu rezonansowego RLC pomniejszoną o wartość M.
% f - częstotliwość (Hz)

    R = 525;            
    C = 7e-5;          
    L = 3;             
    M = 75;             

    if f <= 0
        error('czestotliwosc musi być wieksza od zera.');
    end

    a = 1 / R.^2;
    b = (2 * pi * f * C - 1 / (2 * pi * f * L)).^2;
    Z_mod = 1 / sqrt(a + b);

    impedance_delta = Z_mod - M;
end



