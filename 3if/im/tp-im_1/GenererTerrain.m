function [ terrain ] = GenererTerrain (initterrain, nsubdiv, alpha, lambda)
terrain = Subdivise(initterrain, alpha);
for i = 1:nsubdiv - 1
  alpha = lambda * alpha;
  terrain = Subdivise(terrain, alpha);
end
terrain = Subdivise(terrain, 0);
end