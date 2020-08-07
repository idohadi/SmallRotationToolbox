function P = atan22(X, Y)
%%
% Calculates atan2, with the convention that theta in [0,pi] and phi in
% [0,2pi].
% 
% Input arguments
%   X   double      x coordinates of the vector.
%   Y   double      y coordiantes of the vector.
% X, Y must have the same dimensions.
% 
% Output arguments
%   P   double      Numbers in [0,pi].
% 
% Notes
%   (1) This function performs no input checks.
%   (2) Compared to MATLAB's atan2, the roles of X and Y are the same, but
%       their order in the function call is reversed.
% 
% Reference
%   None
% ***********************************************************
% Author    Ido Hadi
% Email     idohadi@mail.tau.ac.il
% Year      2020
% ***********************************************************

P = atan2(Y, X);
negP = P<0;
P(negP) = P(negP) + 2*pi;
