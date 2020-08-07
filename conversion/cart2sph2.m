function [theta, phi, rho] = cart2sph2(x, y, z)
%%
% Convert a vector in R^3 from Cartesian coordinates to spherical 
% coordinates.
% 
% Convention
%   Variable    Interval
%   theta       [0,pi]
%   phi         [0,2pi)
%   rho         [0,infinity)
% 
% theta, phi, rho satisfy
%   x(j) = rho*cos(phi)*sin(theta)
%   y(j) = rho*sin(phi)*sin(theta)
%   z(j) = rho*cos(theta)
% 
% Input arguments
%   x   double      x coordinates of the vector.
%   y   double      y coordiantes of the vector.
%   z   double      z coordiantes of the vector.
%   x, y, z must have the same dimensions.
% 
% Output arguments
%   theta       See convention.
%   phi         [0,2pi)
%   rho         [0,infinity)
% 
% Notes
%   This function performs no input checks.
% 
% Reference
%   None
% ***********************************************************
% Author    Ido Hadi
% Email     idohadi@mail.tau.ac.il
% Year      2020
% ***********************************************************
%% Cartesian->Spherical coordiantes
% TODO
