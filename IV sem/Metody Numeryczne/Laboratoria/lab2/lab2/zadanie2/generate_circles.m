function [circle_areas, circles, a, b, r_max] = generate_circles(n_max)
% a - szerokosc, b - wysokosc, r_max - max promien okregu n_max - ile chcemy wygenerowac
    % wymiary prostokata
    a = randi([150, 250]);
    b = randi([50, 100]);
    
    %pole prostokata
    rectangle_area = a * b;
    
    % maksymalny promien
    r_max = randi([20, 50]);
    
    %macierz okregow
    circles = zeros(n_max, 3);
    
    %wektor do pol okregow
    circle_areas = zeros(n_max, 1);
    
    % petla generujaca okręgi
    for i = 1:n_max
        valid = false;
        while ~valid %dopoki okrag nie jest ok
             % losowanie promienia okręgu
            R = rand() * (r_max - 1) + 1; %z przedzialu (0,r_max]
            
            % losowanie współrzędnych środka okręgu
            X = rand() * (a - 2 * R) + R; %w przedziale [R, a-R] tak aby miescil sie w prostokacie to samo dla Y
            Y = rand() * (b - 2 * R) + R;
            
            % sprawdzenie kolizji z innymi okregami
            valid = true;
            for j = 1:(i-1) %iterujemy po wszystkich poprzednich
                Xj = circles(j, 1);
                Yj = circles(j, 2);
                Rj = circles(j, 3);
                
                dist = sqrt((X - Xj)^2 + (Y - Yj)^2); %odleglosc miedzy srodkami okregow
                
                %kolizje
                if dist < (R + Rj) || (Rj >= R && dist + R <= Rj) || (R >= Rj && dist + Rj <= R)
                    valid = false;
                    break;
                end
            end
        end
        
        %zapisanie poprawnych wartosci
        circles(i, :) = [X, Y, R];
        
        %suma pol okregow w %
        areas = pi * circles(1:i, 3).^2;  %pola wszystkich okregow
        circle_areas(i) = sum(areas) / rectangle_area * 100;  % %pola prostokata
    end
    
    figure;
    plot(1:n_max, circle_areas);
    xlabel('Liczba okregow');
    ylabel('Stosunek sumy pol okregow do pola prostokata (%)');
    title('Skumulowany stosunek sumy pol okregow do pola prostokata');
    grid on;
    
    saveas(gcf, 'zadanie2.png');
end
