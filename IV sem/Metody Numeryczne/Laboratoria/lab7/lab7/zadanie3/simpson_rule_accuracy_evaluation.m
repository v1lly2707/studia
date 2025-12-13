function [ft_5, integral_1000, Nt, integration_error] = simpson_rule_accuracy_evaluation()
    % Funkcja służy do numerycznego obliczania całki oznaczonej metodą Simpsona
    % z funkcji gęstości prawdopodobieństwa awarii urządzenia elektronicznego.
    % Jej celem jest porównanie dokładności obliczeń
    % w zależności od liczby zastosowanych podprzedziałów całkowania.
    %
    % ft_5 – wartość funkcji gęstości prawdopodobieństwa obliczona dla t = 5.
    %
    % integral_1000 – przybliżona wartość całki oznaczonej na przedziale [0, 5]
    %   wyznaczona metodą Simpsona dla liczby podprzedziałów wynoszącej 1000.
    %
    % integration_error – wektor zawierający błędy bezwzględne numerycznego
    %   wyznaczenia wartości całki oznaczonej. Wartość integration_error(1,i)
    %   oznacza błąd obliczenia całki dla Nt(1,i) podprzedziałów:
    %   integration_error(1, i) = abs(integral_approximation - reference_value),
    %   gdzie reference_value to wzorcowa wartość całki.
    %
    % Nt – wektor wierszowy zawierający liczby podprzedziałów całkowania,
    %   dla których wyznaczane są przybliżenia całki i obliczany jest błąd.

    reference_value = 0.0473612919396179; % wartość referencyjna całki

    ft_5 = failure_density_function(5);
    N = 1000;
    x = linspace(0, 5, N + 1);
    integral_1000 = simpson_rule(x);

    Nt = 5:50:10^4;
    integration_error = zeros(1, length(Nt));

    for i = 1:length(Nt)
        n = Nt(i);
 
        
        x_i = linspace(0, 5, n + 1);
        approx = simpson_rule(x_i);
        integration_error(i) = abs(approx - reference_value);
    end

    loglog(Nt, integration_error);
    xlabel('Liczba podprzedziałów całkowania');
    ylabel('Błąd całkowania');
    title('Dokładność metody Simpsona');
    grid on;
    saveas(gcf, 'zadanie3.png');
end


function integral_approximation = simpson_rule(x)
    % Oblicza przybliżoną wartość całki oznaczonej z funkcji gęstości
    % prawdopodobieństwa (failure_density_function) przy użyciu
    % metody Simpsona.
    %
    % x – wektor rosnących wartości określających końce przedziałów całkowania.
    %     Dla n-elementowego wektora x zdefiniowanych jest n−1 przedziałów
    %     całkowania: [x(1), x(2)], [x(2), x(3)], ..., [x(n−1), x(n)].
    %
    % integral_approximation – przybliżona wartość całki oznaczonej

    n = length(x) - 1;
    dx = x(2) - x(1);
    r = 0;

    for i = 1:n
        x0 = x(i);
        x1 = x(i + 1);
        xm = (x0 + x1) / 2;

        f0 = failure_density_function(x0);
        f1 = failure_density_function(x1);
        fm = failure_density_function(xm);

        r = r + (dx / 6) * (f0 + 4 * fm + f1);
    end

    integral_approximation = r;
end


function ft = failure_density_function(t)
    % Zwraca wartości funkcji gęstości prawdopodobieństwa wystąpienia awarii
    % urządzenia elektronicznego dla zadanych wartości czasu t.
    %
    % t – wektor wartości czasu (wyrażonych w latach), dla których obliczane
    %   są wartości funkcji gęstości prawdopodobieństwa.
    %
    % ft – wektor zawierający wartości funkcji gęstości prawdopodobieństwa
    %      odpowiadające kolejnym elementom wektora t.

    ft = exp(1).^((-(t - 10).^2) ./ (2 * 9)) ./ (3 * sqrt(2 * pi));
end
