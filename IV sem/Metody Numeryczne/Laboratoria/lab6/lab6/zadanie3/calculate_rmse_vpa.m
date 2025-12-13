function [dates, y, rmse_values, M, c_vpa, ya] = calculate_rmse_vpa()
% W tej funkcji obliczenia wykonywane są na zmiennych vpa, jednakże spośród
% zwracanych zmiennych tylko c_vpa jest wektorem zmiennych vpa.
%
% Funkcja calculate_rmse_vpa:
% 1) Wyznacza pierwiastek błędu średniokwadratowego w zależności od stopnia
%    aproksymacji wielomianowej danych przedstawiających produkcję energii.
% 2) Wyznacza i przedstawia na wykresie aproksymację wielomianową wysokiego
%    stopnia danych przedstawiających produkcję energii.
% Dla kraju C oraz źródła energii S:
% dates - wektor energy_2025.C.S.Dates (daty pomiaru produkcji energii)
% y - wektor energy_2025.C.S.EnergyProduction (poziomy miesięcznych produkcji energii)
% rmse_values(i,1) - RMSE wyznaczony dla wektora y i wielomianu stopnia degrees(i)
%     Rozmiar kolumnowego wektora wynosi length(y)-1.
% M - stopień wielomianu aproksymacyjnego przedstawionego na wykresie
% c_vpa - współczynniki wielomianu aproksymacyjnego przedstawionego na wykresie:
%       c = [c_M; ...; c_1; c_0]
% ya - wartości wielomianu aproksymacyjnego wyznaczone dla punktów danych
%       (rozmiar wektora ya powinien być taki sam jak rozmiar wektora y)

    digits(120); % określa liczbę cyfr dziesiętnych w zmiennych vpa

    M = 95; %stopień wielomianu aproksymacyjnego

    load energy_2025

    dates = energy_2025.Poland.Wind.Dates;
    y = energy_2025.Poland.Wind.EnergyProduction;

    N = numel(y);
    
    degrees = [N-10, N-1]; 

    x_vpa = linspace(vpa(0),vpa(1),N)';
    y_vpa = vpa(y);

    rmse_values = zeros(numel(degrees),1);

    % Oblicz RMSE dla każdego stopnia
    for id = 1:numel(degrees)
        m = degrees(id);
        c = polyfit_qr_vpa(x_vpa, y_vpa, m);
        c = c(end:-1:1); 
        y_approx = polyval_vpa(c, x_vpa);
        error = y_approx - y_vpa;
        rmse = sqrt(sum(error.^2) / N);
        rmse_values(id) = double(rmse);
    end

    % Aproksymacja wielomianu wysokiego stopnia (dla wykresu)
    c_vpa = polyfit_qr_vpa(x_vpa, y_vpa, M);
    c_vpa = c_vpa(end:-1:1); % odwrócenie kolejności wektora c_vpa: dostosowanie do polyval

    ya = double(polyval_vpa(c_vpa, x_vpa));
    x = double(x_vpa);

    figure('Units','normalized','Position',[0.1 0.1 0.8 0.8]);

    subplot(2,1,1);
    plot(degrees, rmse_values, 'b.-');
    xlabel('Stopień wielomianu');
    ylabel('RMSE');
    title('RMSE w zależności od stopnia wielomianu aproksymacyjnego');
    grid on;
    legend('RMSE');

    subplot(2,1,2);
    plot(dates, y, 'ko', 'DisplayName', 'Dane oryginalne'); hold on;
    plot(dates, ya, 'r-', 'DisplayName', sprintf('Wielomian stopnia %d', M));
    xlabel('Data');
    ylabel('Produkcja energii');
    title('Aproksymacja wielomianowa danych (vpa)');
    legend;
    grid on;

    saveas(gcf, 'zadanie3.png');
end


function y = polyval_vpa(coefficients, x)
% Oblicza wartość wielomianu w punktach x dla współczynników coefficients.
% Obliczenia wykonywane są na zmiennych vpa.
% coefficients – wektor współczynników wielomianu w kolejności od najwyższej potęgi
% x – wektor argumentów (zmienne vpa)
% y – wektor wartości wielomianu (zmienne vpa)
    n = length(coefficients);
    y = vpa(zeros(size(x))); % inicjalizacja wyniku jako vpa

    for i = 1:n
        y = y .* x + coefficients(i);  % schemat Hornera
    end
end

function c_vpa = polyfit_qr_vpa(x, y, M)
    % Wyznacza współczynniki wielomianu aproksymacyjnego stopnia M
    % z zastosowaniem rozkładu QR.
    % c_vpa - kolumnowy wektor wsp. wielomianu c_vpa = [c_0; ...; c_M]
    %         zawierający zmienne vpa.

    A = vpa(zeros(numel(x), M+1));

    for i = 1:M+1
        A(:, i) = vpa(x).^vpa(i-1); 
    end

    [Q, R] = qr(A, vpa(0));  
    c_vpa = vpa(R) \ (vpa(Q)' * vpa(y));  
end

