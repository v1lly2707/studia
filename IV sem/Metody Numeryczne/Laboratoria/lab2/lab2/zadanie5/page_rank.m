function [index_number,Edges, I, B, A, b, r] = page_rank()
    % macierz krawedzi
    index_number = 197725;
    Edges = [1,1,2,2,2,3,3,3,4,4,5,5,6,6,7,2;
        6,4,3,4,5,5,6,7,5,6,4,6,4,7,6,6];

    % liczba stron w sieci
    N = 7;

    % wspolczynnik tlumienia
    d = 0.85;

    % macierz jednostkowa
    I = speye(N);

    % macierz sasiedztwa
    B = sparse(Edges(2,:), Edges(1,:), 1, N, N);

    % macierz diagonalna
    S = sum(B, 1);  % suma elem w kolumnach macierzy A
    A = spdiags(1 ./ S', 0, N, N);

    % macierz ukladu rownan
    M = I - d * B * A;

    % wektor prawej strony rownania
    b = (1 - d) / N * ones(N, 1);

    % rozwiazania ukladu rownan
    r = M \ b;

    % wykres
    figure;
    bar(r);
    title('PageRank dla sieci stron');
    xlabel('Numer strony');
    ylabel('Wartość PageRank');
    saveas(gcf, 'zadanie5.png');  
end