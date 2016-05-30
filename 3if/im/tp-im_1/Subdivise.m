function [ terr ] = Subdivise (terrain,alpha)

% variables
[tm, tn] = size (terrain);


% Création de la seconde matrice 2 fois plus grande
sm = 2*tm - 1;
sn = 2*tn - 1;
terr = zeros(sm,sn);

% Copie de la premiere matrice
terr(1:2:sm,1:2:sn) = terrain;

% Première étape : somme des elements diagonaux (diamond)
alea = rand(size(terrain) - 1)*2*alpha - alpha;
terr(2:2:sm-1,2:2:sn-1) = (terrain(1:tm-1,1:tn-1) +...
                           terrain(2:tm,  1:tn-1) +...
                           terrain(1:tm-1,2:tn)   +...
                           terrain(2:tm,  2:tn)...
                           )/4 + alea;

% Deuxième étape (square)
%% Partie 1 : cotés gauche et droit
alea = range(rand(tm - 1,2),alpha);
terr (2:2:sm - 1,[1,sn]) = ( terr(1:2:sm - 2, [1,sn]) + terr(3:2:sm, [1,sn]) ) / 2 + alea;
%% Partie 2 : haut et bas
alea = range(rand(2,tn - 1),alpha);
terr ([1,sm],2:2:sn - 1) = (terr([1,sm],1:2:sn - 2) + terr([1,sm],3:2:sn)) / 2 + alea;
%% Partie 3 : colonnes pair
alea = range(rand(tm-2,tn-1),alpha);
terr (3:2:sm-1,2:2:sn-1) = (terr(2:2:sm-2, 2:2:sn-1) +...
                            terr(4:2:sm,   2:2:sn-1) +...
                            terr(3:2:sm-1, 1:2:sn-1) +...
                            terr(3:2:sm-1, 3:2:sn)...
                           )/4 + alea;
%% Partie 4 : colonnes impair
alea = range(rand(tm-1,tn-2),alpha);
terr (2:2:sm-1,3:2:sn-1) = (terr(1:2:sm-1, 3:2:sn-1) +...
                            terr(3:2:sm,   3:2:sn-1) +...
                            terr(2:2:sm-1, 2:2:sn-2) +...
                            terr(2:2:sm-1, 4:2:sn)...
                           )/4 + alea;

end

function [ret] = range(a,alpha)
ret = a*2*alpha - alpha;
end