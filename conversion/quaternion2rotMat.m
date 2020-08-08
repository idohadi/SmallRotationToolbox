function rotMat = quaternion2rotMat(quaternion)
%%
% Call format
%   rotMat = quaternion2rotMat(quaternion)
% 
% Convert rotations from quaternion representation to rotation matrix 
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
%   rotMat          double      3 x 3 x N array, such that rotMat(:, :, n)
%                               is a rotation matrix.
% 
% Output arguments
%   quaternion      double      4 x N array, such that quaternion(:, n) is 
%                               a quaternion representation of the rotation 
%                               represented by rotMat(:, :, n).
% 
% Notes
%   (1) An introduction to quaternions and their use in rotation formalism can 
%       be found in [1].
%   (2) This function uses a numerically naive method. It doesn't attempt
%       to maintain numerical stability.
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
    rotMat = [];
    warning('The input rotation array is empty.');
    return;
end

assert(size(quaternion, 1)==4, ...
    ['Rotations must be represented in quaternion representation. ', ...
    'In particular, rotation array must have 4 rows.']);

%% Quaternion->rotation matrix
rotMat = zeros([3, 3, size(quaternion, 2)]);
for J=1:size(quaternion, 2)
    Q = zeros(3, 3);
    Q([6, 7, 2, 8, 3, 4]) = [quaternion(2:end, J); -quaternion(2:end, J)];
    rotMat(:, :, J) = (quaternion(1, J)^2 - quaternion(2:end, J)'*quaternion(2:end, J)) * eye(3) ...
        + 2 * quaternion(2:end, J)*quaternion(2:end, J)' ...
        + 2 * quaternion(1, J)*Q;
end
