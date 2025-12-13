function [rand_counts, counts_mean, circles, a, b, r_max] = generate_circles(n_max)
% a - szerokosc, b - wysokosc, r_max - max promien okregu n_max - ile chcemy wygenerowac
    % wymiary prostokata
    a = randi([150, 250]);
    b = randi([50, 100]);
    
    % maksymalny promien
    r_max = randi([20, 50]);
    
    % macierz okregow
    circles = zeros(n_max, 3);
    
    % wektory do przechowywania liczby losowan i ich sredniej
    rand_counts = zeros(1, n_max);  
    counts_mean = zeros(1, n_max);

    % petla generująca okregi
    for i = 1:n_max
        valid = false;
        count = 0;  % licznik losowan dla danego okregu

        while ~valid %dopoki okrag nie jest ok
            count = count + 1;  % zliczanie prob losowania

            % losowanie promienia okregu
            R = rand() * (r_max - 1) + 1; %z przedzialu (0,r_max]

            % losowanie wspolrzędnych srodka okregu
            X = rand() * (a - 2 * R) + R; %w przedziale [R, a-R] tak aby miescil sie w prostokacie to samo dla Y
            Y = rand() * (b - 2 * R) + R;

            % sprawdzenie kolizji z innymi okregami            
            valid = true;
            for j = 1:(i-1) %iterujemy po wszystkich poprzednich
                Xj = circles(j, 1);
                Yj = circles(j, 2);
                Rj = circles(j, 3);
                
                dist = sqrt((X - Xj)^2 + (Y - Yj)^2); %odleglosc miedzy srodkami okregow
                
                if dist < (R + Rj) || (Rj >= R && dist + R <= Rj) || (R >= Rj && dist + Rj <= R)
                    valid = false;
                    break;
                end
            end
        end

        %zapisanie poprawnych wartosci
        circles(i, :) = [X, Y, R];

        %zapisanie liczby prob losowania
        rand_counts(i) = count;

        %srednia liczba losowan
        counts_mean(i) = mean(rand_counts(1:i));
    end

    %wykresy
    figure;
    
    
    subplot(2, 1, 1);
    plot(1:n_max, rand_counts);
    xlabel('Numer okręgu');
    ylabel('Liczba losowań');
    title('Liczba losowań dla każdego okręgu');
    grid on;

    
    subplot(2, 1, 2);
    plot(1:n_max, counts_mean);
    xlabel('Numer okręgu');
    ylabel('Srednia liczba losowan');
    title('Srednia liczba losowan na kolejnych etapach');
    grid on;

    
    saveas(gcf, 'zadanie3.png');
end
