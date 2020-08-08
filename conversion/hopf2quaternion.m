function quaternion = hopf2quaternion(hopf)
%%
% Call format
%   quaternion = hopf2quaternion(hopf)
% 
% Convert rotations from Hopf representation to quaternion representation.
% 
% Convention
%   hopf is a representation of a rotation. It is a 3-dimensional vector.
%   Naming its coordinates:
%       Variable    Array       Interval
%       theta       hopf(1)     [0,2pi)
%       phi         hopf(2)     [0,pi]
%       psi         hopf(3)     [0,2pi)
% 
%   q is a quaternion represntation of rotation.
%       Variable    Array       Interval
%       free        q(1)        [0,1)
%       i           q(2)        [-1,1]
%       j           q(3)        [-1,1]
%       k           q(4)        [-1,1]
%   q satisfies
%       q(1)^2 + q(2)^2 + q(3)^2 + q(4)^2 = 1
% 
%   theta, phi, psi and q satisfy
%       q(1) = cos(0.5*theta) * cos(0.5*psi)
%       q(2) = cos(0.5*theta) * sin(0.5*psi)
%       q(3) = sin(0.5*theta) * cos(phi + 0.5*psi)
%       q(4) = sin(0.5*theta) * sin(phi + 0.5*psi)
% 
% 
% Input arguments
%   hopf           double       3 x N array, such that hopf(:, n) is the 
%                               Hopf representation of a rotation.
% 
% Output arguments
%   quaternion     double       4 x N array, such that quaternion(:, n) is 
%                               a quaternion representation of the rotation 
%                               represented by hopf(:, n).
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
