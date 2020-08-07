function rotation = randRotation(N)
%%
% Indepently and uniformly sample N rotations, in quaternion
% representation.
% 
% Input arguments
%   N           double      
% 
% Output arguments
%   rotation    double      4 x N array, such that rotation(:, n) is a unit
%                           quaternion representing a rotation.
% 
% Notes
%   This is an implementation of the method described in [1], section
%   5.2.2 (p. 164).
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
assert(isscalar(N) && N>=1 && round(N)==N, ...
    'Number of rotations must be a positive integer.');

%% Uniformly sampling rotations
u1 = rand(1, N);
u2 = rand(1, N);
u3 = rand(1, N);
rotation = [sqrt(1-u1).*sin(2*pi*u2); ...
            sqrt(1-u1).*cos(2*pi*u2); ...
            sqrt(u1).*sin(2*pi*u3); ...
            sqrt(u1).*cos(2*pi*u3)];

% Ensure the first element in the quaternion is non-negative
negFirstEl = rotation(1, :)<0;
rotation(:, negFirstEl) = - rotation(:, negFirstEl);
