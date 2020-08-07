function hopf = quaternion2hopf(quaternion)
% TODO: convert rotations from quaternion to hopf coordinates
%%
% Convert rotations from quaternion representation to Hopf representation.
% 
% Convention
%   Variable    Input           Interval
%   theta       hopf(1, :)      [0,2pi)
%   phi         hopf(2, :)      [0,pi]
%   psi         hopf(3, :)      [0,2pi)
% 
% theta, phi, psi satisfy
%   quaternion(1, j) = cos(0.5*theta(j)) .* cos(0.5*psi(j))
%   quaternion(2, j) = cos(0.5*theta(j)) .* sin(0.5*psi(j))
%   quaternion(3, j) = sin(0.5*theta(j)) .* cos(phi(j) + 0.5*psi(j))
%   quaternion(4, j) = sin(0.5*theta(j)) .* sin(phi(j) + 0.5*psi(j))
% 
% Input arguments
%   quaternion     double       4 x N array, such that quaternion(:, j) is 
%                               the Hopf coordiantes representation of
%                               rotation.
% 
% Output arguments
%   hopf           double       3 x N array, such that hopf(:, j) is the 
%                               Hopf coordiantes representation of
%                               rotation.
% 
% Notes
%   (1) An expalantion of Hopf representation of rotations and Hopf fibration
%       in general can be found in [1].
%   (2) An introduction to quaternions and their use in rotation formalism
%       can be found in [2].
% 
% Reference
%   [1] Lyons, D. W. (2003). An Elementary Introduction to the Hopf 
%       Fibration. Mathematics Magazine, 76(2), 87–98. 
%       https://doi.org/10.1080/0025570X.2003.11953158
%   [2] http://graphics.stanford.edu/courses/cs348a-17-winter/Papers/quaternion.pdf
% ***********************************************************
% Author    Ido Hadi
% Email     idohadi@mail.tau.ac.il
% Year      2020
% ***********************************************************
%% Input validation
if isempty(quaternion)
    quaternion = [];
    warning('The input rotation array is empty.');
    return;
end

assert(size(rotation, 1)==4, ...
    ['Rotations must be represented in quaternion representation. ', ...
    'In particular, rotation array must have 4 rows.']);

%% qutaernion->Convert Hopf
% TODO
