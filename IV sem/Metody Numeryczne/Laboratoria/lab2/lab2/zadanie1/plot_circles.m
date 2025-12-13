function plot_circles(a, b, circles)
    % Tworzenie nowego wykresu
    figure;
    
    % Ustawienie właściwości osi i rysowanie prostokąta jako tła
    axis equal;
    axis([0 a 0 b]);
    hold on;

    % Pętla rysująca wszystkie okręgi
    for i = 1:size(circles, 1)
        X = circles(i, 1);
        Y = circles(i, 2);
        R = circles(i, 3);
        
        % Rysowanie okręgu za pomocą wcześniej przygotowanej funkcji plot_circle
        plot_circle(X, Y, R);
        
        % Opcjonalne opóźnienie, aby zobaczyć proces rysowania
        pause(0.1);
    end
    
    % Zatrzymanie funkcji hold, aby zakończyć rysowanie
    hold off;
end
