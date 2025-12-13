function [circles, a, b, r_max] = generate_circles(n_max)
% a - szerokosc, b - wysokosc, r_max - max promien okregu n_max - ile chcemy wygenerowac
    % wymiary prostokata
    a = randi([150, 250]);
    b = randi([50, 100]);
    
    % maksymalny promien
    r_max = randi([20, 50]);
    
    %  macierz okręgow
    circles = zeros(n_max, 3);
    
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
                
                if dist < (R + Rj)  % okregi nie mogą się przecinac
                    valid = false;
                    break;
                end
                
                if Rj >= R && dist + R <= Rj  % okrag nie może być w innym
                    valid = false;
                    break;
                end
                
                if R >= Rj && dist + Rj <= R  % okrag nie może zawierać innego
                    valid = false;
                    break;
                end
            end
        end
        
        %zapisanie poprawnych wartosci
        circles(i, :) = [X, Y, R];
    end
end

