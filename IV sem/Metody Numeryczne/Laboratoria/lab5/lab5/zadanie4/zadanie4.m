clear all
close all

[matrix_sizes, condition_numbers, interpolation_error_exact, interpolation_error_perturbed] = ...
    vpa_ill_conditioning_demo();

saveas(gcf, 'zadanie4.png');