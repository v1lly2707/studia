function velocity_delta = velocity_difference(t)
% Wyznacza prędkość rakiety po czasie t od startu pomniejszoną o wartość M.
% t - [s] czas od startu rakiety
% velocity_delta [m/s] - różnica między aktualną prędkością a 700 m/s

m0 = 150000;      
q = 2700;        
u = 2000;       
g = 1.622;       
M = 700; 

if t <= 0
    error('Przerwanie działania');
end

v = u * log(m0 / (m0 - q * t)) - g * t;

velocity_delta = v - M;

end
