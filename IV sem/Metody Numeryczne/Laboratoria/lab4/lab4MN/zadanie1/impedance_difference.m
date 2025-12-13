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
