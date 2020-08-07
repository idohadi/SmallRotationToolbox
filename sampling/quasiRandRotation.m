function rotation = quasiRandRotation(n, varargin)
%%
% Return the nth point from a quasi-random, well-dispersed grid on the
% rotation group SO(3).
% 
% Call format
%   rotation = quasiRandRotation(n)
%   rotation = quasiRandRotation(n, 'quaternion')
%   rotation = quasiRandRotation(n, 'hopf')
% 
% Input arguments
%   n                   double          N x 1 or 1 x N array, of integers.
%                                       They must be positive.
% 
% Output arguments
%   rotation            double          4 x N array in quaternion 
%                                       representation or 3 x N in Hopf
%                                       representation.
%                                       rotation(:, i) = the n(i)th
%                                       rotation in the quasi-random
%                                       rotation grid.
% 
% Optional arguments
%   Name                Default         Definition
%   representation      'quaternion'    Decides whether rotation is in
%                                       quaternion representation or Hopf
%                                       representation.
% 
% Notes
%   (1) This function performs no input checks on n.
%   (2) This function wraps the mex function quasiRandRotation_mex.
%   (3) This is an implementation of the algorithm of [1]. The main
%       functions are written in C. The C code is derived from the Authors'
%       C++ code. Their original C++ code is available at
%           https://mitchell-web.ornl.gov/SOI/index.php
%       under "ISOI_SO3_sequence.tgz".
%   (4) 
%   TODO: add a reference or an explanation of Hopf coordiantes
%   TODO: in particular explain the Hopf coordiantes I used:
%           name        coordinate      interval
%           theta       1               [0,2pi)
%           phi         2               [0,pi]
%           psi         3               [0,2pi)
% 
% Reference
%   [1] Yershova, A., Jain, S., LaValle, S. M., & Mitchell, J. C. (2009). 
%       Generating Uniform Incremental Grids on SO(3) Using the Hopf 
%       Fibration. The International Journal of Robotics Research, 29(7), 
%       801–812. https://doi.org/10.1177/0278364909352700
% ***********************************************************
% Author    Ido Hadi
% Email     idohadi@mail.tau.ac.il
% Year      2020
% ***********************************************************
%% Input validation
narginchk(1, 2);

if nargin==1
    qFlag = true;
else
    qFlag = strcmp(varargin{1}, 'quaternion');
end

%% Genearte grid points
rotation = quasiRandRotation_mex(n);
if qFlag
    rotation = hopf2quaternion(rotation);
end
