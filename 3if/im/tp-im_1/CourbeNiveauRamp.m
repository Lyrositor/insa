function [texture] = CourbeNiveauRamp( terrain, inter, rampfile )
% creation des courbes de niveau
texture_niveau = CourbeNiveau (terrain, inter);

% creation de la ramp
ramp = imread(rampfile);
terrain = (terrain - min(min(terrain))) / ( max(max(terrain)) - min(min(terrain))) * (size(ramp,2)-1);
line_ramp = ramp(1,round(terrain)+1,:);
texture_ramp = reshape(line_ramp, size(terrain, 1), size(terrain, 2), 3);

% association des deux
%texture = bitand(uint8(texture_ramp),uint8(texture_niveau));
texture = uint8(texture_ramp);
end

