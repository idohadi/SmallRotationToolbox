%% rotationGrid_demo
% This file demonstrates the properties of the quasi-random, incremental
% sequence of rotations.
% This sequence is generated using the algorithm of [1].
% 
% Reference
%   [1] Yershova, A., Jain, S., LaValle, S. M., & Mitchell, J. C. (2009). 
%       Generating Uniform Incremental Grids on SO(3) Using the Hopf 
%       Fibration. The International Journal of Robotics Research, 29(7), 
%       801–812. https://doi.org/10.1177/0278364909352700

%% A visual representation of the sequence
% For the first 6 levels of the Display every level in the sequence in a 
% different color.

levels = 6;

figure;
hold;
sz = 8;

cmap = colormap('hsv');

rotations = quasiRandRotation(1:72, 'hopf');
color = cmap(1, :);
scatter3(rotations(1, :), rotations(2, :), rotations(3, :), ...
    sz, color, 'filled');

for J=1:levels-1
    rotations = quasiRandRotation(72*2^J+1:72*2^(J+1), 'hopf');
    color = (size(cmap, 1)-1)/(J+1);
    color ...
        = abs([floor(color+1)-(color+1), ceil(color+1)-(color+1)]) ...
        *[cmap(floor(color+1), :); cmap(ceil(color+1), :)];
    scatter3(rotations(1, :), rotations(2, :), rotations(3, :), ...
        sz, color, 'filled');
end
hold off;

view(3);
xlabel('\theta');
ylabel('\phi');
zlabel('\psi');
title(['First ', num2str(levels), ' Levels of Quasi-Random Sequence']);

%% Approximate dispersion
% Dispersion is a measure of how well a set of rotations "fills" the
% rotation group. 
% Given a set of rotations R, its dispersion is estimated as follows:
% (1) Generate 10^4 uniformly random rotations M.
% (2) Calculate MMin{k} = min_{j} { dist(M(k), R{j} }.
% (3) The dispersion is max(MMin).
% 
% This code estimates the dispersion of the first N points in the sequence,
% for various N.


% Estimate dispersion
K = 10^4;
N = [50, 100, 200, 300, 500, 10^3, 5*10^3, 10^4, 2*10^4, 5*10^4, 8*10^4, 10^5];
rotations = quasiRandRotation(1:N(end));
dispersion = arrayfun(@(n) max(min( ...
    rotationDistance(rotations(:, 1:n), randRotation(K)), ...
    [], 1)), N);

% Plot the dispersion
figure;
plot(N, dispersion, ...
    'Marker', 'o', ...
    'MarkerFaceColor', [0 0.4470 0.7410], ...
    'MarkerSize', 8);

title('Estimates of Dispersion');
xlabel('Number of sequence points');
ylabel('Dispersion');
set(gca, 'XScale', 'log')
