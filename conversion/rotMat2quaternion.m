function quaternion = rotMat2quaternion(rotMat)
%%
% Convert rotations from rotation matrix representation to quaternion 
% representation.
% 
% Convention
%   R is rotation matrix. That is, it is 3 x 3 matrix of real doubles such 
%   that
%       R'*R = R*R' = eye(3)
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
%   R and q satisfy
%       q(1) = 0.5 * sqrt(1 + R(1,1) + R(2,2) + R(3,3))
%       q(2) = 0.25*(R(3,2) - R(2,3))/q(1)
%       q(3) = 0.25*(R(1,3) - R(3,1))/q(1)
%       q(4) = 0.25*(R(2,1) - R(1,2))/q(1)
%   and 
%       R = (q(1)^2 - q(2:4)'*q(2:4)) * eye(3) + 2 * q(2:4)*q(2:4)' + 2*q(1)*Q
%   where
%               [ 0     -q(3)    q(2)]
%           Q = [ q(3)   0      -q(1)]
%               [-q(2)   q(1)    0   ]
% 
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
if isempty(rotMat)
    quaternion  = [];
    warning('The input rotation array is empty.');
    return;
end

assert(size(rotMat, 1)==3 && size(rotMat, 2)==3, ...
    ['Rotations must be represented in matrix representation. ', ...
    'In particular, rotation array must be 3 x 3 x N dimensional.']);

%% Rotation matrix->qutaernion
% TODO
