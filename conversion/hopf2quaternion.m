function quaternion = hopf2quaternion(hopf)
%%
% Convert rotations from Hopf representation to quaternion representation.
% 
% Convention
%   hopf is a representation of a rotation. It is a 3-dimensional vector.
%   Naming its coordinates:
%       Variable    Input       Interval
%       theta       hopf(1)     [0,2pi)
%       phi         hopf(2)     [0,pi]
%       psi         hopf(3)     [0,2pi)
% 
%   q is a quaternion. 
%   
%   theta, phi, psi and q satisfy
%       q(1) = cos(0.5*theta) * cos(0.5*psi)
%       q(2) = cos(0.5*theta) * sin(0.5*psi)
%       q(3) = sin(0.5*theta) * cos(phi + 0.5*psi)
%       q(4) = sin(0.5*theta) * sin(phi + 0.5*psi)
% 
% 
% Input arguments
%   hopf           double       3 x N array, such that hopf(:, j) is the 
%                               Hopf coordiantes representation of
%                               rotation.
% 
% Output arguments
%   quaternion     double       4 x N array, such that quaternion(:, j) is 
%                               the Hopf coordiantes representation of
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
