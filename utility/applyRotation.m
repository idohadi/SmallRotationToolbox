function xRot = applyRotation(rotation, x)
%%
% Apply the rotation to vectors in R^3.
% 
% Input arguments
%   rotation    double      4 x M real array, such that rotation(:, m) is a
%                           unit quaternion representing a rotation.
%   x           double      3 x N real array.
% 
% Output arguments
%   xRot        double      3 x N x M real array, 
%                               xRot(:, n, m) = rotation(:, m)*x(:, n).
% 
% Notes
%   This is a wrapper of the mex function applyRotation_mex.
% 
% Reference
%   None
% ***********************************************************
% Author    Ido Hadi
% Email     idohadi@mail.tau.ac.il
% Year      2020
% ***********************************************************
%% Input validation
assert(ismatrix(x), 'x must be a matrix.');
if isempty(x)
    xRot = [];
    warning('x is empty.');
    return;
end
assert(size(x, 1)==3, 'x must have 3 rows.'); 

if isempty(rotation)
    xRot = x;
    warning('Rotation is empty.');
    return;
end
assert(size(rotation, 1)==4, ...
    ['Rotation must be a unit quaternion. ', ...
    'In particular, it must have 4 rows.']);

%% Calling the mex function
xRot = splitapply(@(r) applyRotation_mex(r, x), rotation, 1:size(rotation, 2));
% cell2mat(...
%     cellfun(...
%         @(r) applyRotation_mex(r, x), num2cell(rotation), ...
%         'UniformOutput', false ...
%         ) ...
%     );
xRot = reshape(xRot, [size(x), size(rotation, 2)]);
