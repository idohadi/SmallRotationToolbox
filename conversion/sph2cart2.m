function [x, y, z] = sph2cart2(theta, phi, rho)
%%
% Convert a vector in R^3 from spherical coordinates to Cartesian 
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
%   theta       See convention.
%   phi         [0,2pi)
%   rho         [0,infinity)
% 
% Output arguments
%   x   double      x coordinates of the vector.
%   y   double      y coordiantes of the vector.
%   z   double      z coordiantes of the vector.
%   x, y, z must have the same dimensions.
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
%% Spherical coordiantes->Cartesian
% TODO
