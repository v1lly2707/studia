clear all;
close all;
[A,b,M,w,x,r_norm,iteration_count] = solve_Jacobi();

saveas(gcf, 'zadanie3.png');