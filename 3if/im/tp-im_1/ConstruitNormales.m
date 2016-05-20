function [ normales ] = ConstruitNormales( points )
% construit les vecteurs correpondant à la moyenne des normales des triangles
% formés par le tableau de points 3D donné en argument
% points est un tableau à trois dimensions de taille (h,l,3)
% normales est un tableau à trois dimensions de taille (h,l,3)
% code hautement parallèle sans boucle for

h = size(points,1);
l = size(points,2);

v1 = [points(1:h,1:l-1,:)-points(1:h,2:l,:),zeros(h,1,3)];
v2 = [points(1:h-1,1:l,:)-points(2:h,1:l,:);zeros(1,l,3)];
v3 = [zeros(h,1,3),points(1:h,2:l,:)-points(1:h,1:l-1,:)];
v4 = [zeros(1,l,3);points(2:h,1:l,:)-points(1:h-1,1:l,:)];
normales = cross(v1,v2) + cross(v2,v3) + cross(v3,v4) + cross(v4,v1);
norms  = sqrt(sum(normales.^2,3));
normales(:,:,1) = normales(:,:,1) ./ norms;
normales(:,:,2) = normales(:,:,2) ./ norms;
normales(:,:,3) = normales(:,:,3) ./ norms;

end

