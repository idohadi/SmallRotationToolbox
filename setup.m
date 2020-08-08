%% Adds the necessary folders to path
[pathstr, ~, ~] = fileparts(mfilename('fullpath'));
addpath(genpath(fullfile(pathstr, 'conversion')));
addpath(genpath(fullfile(pathstr, 'sampling')));
addpath(genpath(fullfile(pathstr, 'utility')));
