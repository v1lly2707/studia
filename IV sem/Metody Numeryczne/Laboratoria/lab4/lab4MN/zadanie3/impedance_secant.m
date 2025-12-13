function [xvec, xdif, xsolution, ysolution, iterations] = impedance_secant()
% Wyznacza miejsce zerowe funkcji impedance_difference metodą siecznych.
% xvec - wektor z kolejnymi przybliżeniami miejsca zerowego;
%   xvec(1)=x2 przy założeniu, że x0 i x1 są punktami startowymi
% xdif - wektor różnic kolejnych przybliżeń miejsca zerowego
%   xdif(i) = abs(xvec(i+1)-xvec(i));
% xsolution - obliczone miejsce zerowe
% ysolution - wartość funkcji impedance_difference wyznaczona dla f=xsolution
% iterations - liczba iteracji wykonana w celu wyznaczenia xsolution

x0 = 1; % pierwszy punkt startowy metody siecznych
x1 = 10; % drugi punkt startowy metody siecznych
ytolerance = 1e-12; % tolerancja wartości funkcji w przybliżonym miejscu zerowym.
% Warunek abs(f1(xsolution))<ytolerance określa jak blisko zera ma znaleźć
% się wartość funkcji w obliczonym miejscu zerowym funkcji f1(), aby obliczenia
% zostały zakończone.
max_iterations = 1000; % maksymalna liczba iteracji wykonana przez alg. bisekcji

f0 = impedance_difference(x0);
f1 = impedance_difference(x1);

xvec = [];
xdif = [];

for ii = 1:max_iterations
    x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
    f2 = impedance_difference(x2);

    xvec(ii,1) = x2;
   

    % Warunek stopu
    if abs(f2) < ytolerance
        xsolution = x2;
        ysolution = f2;
        iterations = ii;
        break
    end

    x0 = x1;
    f0 = f1;
    x1 = x2;
    f1 = f2;
end

for i=1:iterations-1
    xdif(i,1) = abs(xvec(i+1,1)-xvec(i,1));
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

saveas(gcf, 'zadanie3.png');


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
