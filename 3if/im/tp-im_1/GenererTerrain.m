function [terrain] = GenererTerrain(initterrain, nsubdiv, alpha, lambda)
    terrain = Subdivise(initterrain, alpha);
    if nsubdiv > 1
        terrain = GenererTerrain(terrain, nsubdiv - 1, alpha * lambda, lambda);
    end
end