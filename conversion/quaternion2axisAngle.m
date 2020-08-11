function axisAngle = quaternion2axisAngle(quaternion)
%%
% Call format
%   axisAngle = quaternion2axisAngle(quaternion)
% 
% Convert rotations from quaternion representation to axis-angle 
% representation.
% 
% Convention
%   aa is a representation of a rotation. It is a 4-dimensional vector.
%   Naming its coordinates:
%       Variable    Array       Interval
%       phi         aa(1)       [0,2pi)
%       x1          aa(2)       [0,pi]
%       x2          aa(3)       [0,2pi)
%       x3          aa(4)       [0,2pi)
%   aa satisfies 
%       aa(2)^2 + aa(3)^2 + aa(4)^2 = 1
%   aa represents the rotation by phi degrees counterclockwide around
%   (x1,x2,x3).
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
%   phi, x1, x2, x3 and q satisfy
%       q(1) = cos(phi/2)
%       q(2) = sin(phi/2) * x1
%       q(3) = sin(phi/2) * x2
%       q(4) = sin(phi/2) * x3
% 
% 
% Input arguments
%   quaternion     double       4 x N array, such that quaternion(:, n) is 
%                               a quaternion representation of a rotation.
% 
% Output arguments
%   axisAngle       double      4 x N array, such that axisAngle(:, n) is 
%                               the axis-angle representation of the 
%                               rotation represented by quaternion(:, n).
% 
% Notes
%   (1) An introduction to quaternions and their use in rotation formalism
%       can be found in [1].
% 
% Reference
%   [1] http://graphics.stanford.edu/courses/cs348a-17-winter/Papers/quaternion.pdf
% ***********************************************************
% Author    Ido Hadi
% Email     idohadi@mail.tau.ac.il
% Year      2020
% ***********************************************************
%% Input validation
if isempty(quaternion)
    axisAngle = [];
    warning('The input rotation array is empty.');
    return;
end

assert(size(quaternion, 1)==4, ...
    ['Rotations must be represented in quaternion representation. ', ...
    'In particular, rotation array must have 4 rows.']);

%% Qutaernion->axis-angle
axisAngle = zeros(size(quaternion));

N = hypot( ...
                    hypot(quaternion(2, :), quaternion(3, :)), ...
                    quaternion(4, :) ...
                    );

% Calculate 0.5*phi
axisAngle(1, :) = atan22(quaternion(1, :), N);

% Calculate x1, x2 and x3
nnzs = axisAngle(1, :)~=0;
axisAngle(2:end, nnzs) = quaternion(2:end, nnzs)./sin(axisAngle(1, nnzs));

% Calcualte phi
axisAngle(1, :) = 2*axisAngle(1, :);
