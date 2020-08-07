function quaternion = hopf2quaternion(hopf)
%%
% Convert rotations from Hopf representation to quaternion representation.
% 
% Input arguments
%   hopf           double       4 x N array, such that hopf(:, j) is the 
%                               Hopf coordiantes representation of
%                               rotation.
% 
% Output arguments
%   quaternion     double       4 x N array, such that quaternion(:, j) is 
%                               the Hopf coordiantes representation of
%                               rotation.
% 
% Notes
%   TODO: add a reference or an explanation of Hopf coordiantes
%   TODO: in particular explain the Hopf coordiantes I used:
%           name        coordinate      interval
%           theta       1               [0,2pi)
%           phi         2               [0,pi]
%           psi         3               [0,2pi)
% 
% Reference
%   [1] TODO: add a reference
% ***********************************************************
% Author    Ido Hadi
% Email     idohadi@mail.tau.ac.il
% Year      2020
% ***********************************************************
%% Input validation
if isempty(hopf)
    quaternion = [];
    warning('The input rotation array is empty.');
    return;
end

assert(size(hopf, 1)==3, ...
    ['Rotations must be represented in Hopf representation. ', ...
    'In particular, rotation array must have 3 rows.']);

%% Convert Hopf->qutaernion
quaternion = [...
                cos(0.5*hopf(1, :)) .* cos(0.5*hopf(3, :)); ...
                cos(0.5*hopf(1, :)) .* sin(0.5*hopf(3, :)); ...
                sin(0.5*hopf(1, :)) .* cos(hopf(2, :) + 0.5*hopf(3, :)); ...
                sin(0.5*hopf(1, :)) .* sin(hopf(2, :) + 0.5*hopf(3, :))...
             ];
