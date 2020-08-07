function d = rotationDistance(rotation1, rotation2)
%%
% Calculate the distance between the given rotations. The rotations are
% assumed to be represented as unit quaternions with a positive first 
% element.
% 
% Input arguments
%   rotation1       double      4 x N1 array of unit quaternions,
%                               representing rotations.
%   rotation2       double      4 x N2 array of unit quaternions,
%                               representing rotations.
% 
% Output arguments
%   d               double      N1 x N2 array, 
%                                   d(n1, n2) = dist(rotation1(:, n1), rotation2(:, n2)).
% 
% Notes
%   The metric I implemented is the arc distance along the 3-sphere. For
%   details, see section 5.1 in [1] (in particular, p. 157).
% 
% Reference
%   [1] LaValle, S. M. (2006). Planning algorithms. Cambridge university 
%       press.
% ***********************************************************
% Author    Ido Hadi
% Email     idohadi@mail.tau.ac.il
% Year      2020
% ***********************************************************
%% Input validation
if isempty(rotation1) || isempty(rotation2)
    d = [];
    warning('A rotation array is empty.');
    return;
end

assert(size(rotation1, 1)==4 && size(rotation2, 1)==4, ...
    ['Rotations must be represented in unit quaternions. ', ...
    'In particular, rotation arrays must have 4 rows.']);

%% Calculate distance
d = zeros(size(rotation1, 2), size(rotation2, 2));
rotation1 = rotation1';
for J=1:size(rotation2, 2)
    d(:, J) = acos(abs(rotation1)*rotation2(:, J));
end
