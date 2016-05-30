function [ texture ] = Ombrage( terrain, inter, rampfile, normales, lumiere)
    texture_ramp = double(CourbeNiveauRamp(terrain, inter, rampfile));
    mod = (normales(:,:,1) * lumiere(1) + normales(:,:,2) * lumiere(2) + normales(:,:,3) * lumiere(3))/norm(lumiere);
    mod(mod<0.1) = 0.1;
    texture_ligne = [texture_ramp(:,:,1) .* mod texture_ramp(:,:,2) .* mod texture_ramp(:,:,3) .* mod];
    texture = reshape(texture_ligne, size(terrain, 1), size(terrain, 2), 3);
    texture = uint8(texture);
end

