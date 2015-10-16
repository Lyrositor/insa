function [] = probleme_chauffage_plaque()
    % Construction de A
    A = zeros(450);
    [A_i, A_j] = size(A);
    for k=1:A_i
        [i, j] = b(k);
        A(k, k) = -4;

        % Voisin en haut
        if i ~= 1
            A(k, c(i - 1, j)) = 1;
        else
            A(k, k) = -3;
        end
        
        % Voisin en bas
        if i ~= 15
            A(k, c(i + 1, j)) = 1;
        else
            A(k, k) = -3;
        end
        
        % Voisin gauche
        if j ~= 1
            A(k, c(i, j - 1)) = 1;
        else
            A(k, c(i, 12)) = 1;
        end
        
        % Voisin droit
        if j ~= 30
            A(k, c(i, j + 1)) = 1;
        else
            A(k, c(i, 12)) = 1;
        end

        % Voisins du pli
        if j == 12
            if i ~= 1 && i ~= 15
                A(k, k) = -6;
            else
                A(k, k) = -5;
            end
            A(k, c(i, 1)) = 1;
            A(k, c(i, 30)) = 1;
        end
    end
    
    % Construction de B
    B = zeros(450, 1);
    for j=16:18
        B(c(8, j)) = 300;
    end
    
    % Calcul de X
    X = B;
    while true
        % Refroidissement
        X = expm(A*1)*X;
        surf(reshape(X, 15, 30));
        hold on
        axis([0 30 0 15 150 300])
        hold off
        pause(0.1);
        
        % Réchauffement
        for j=16:18
            X(c(8, j)) = 300;
        end
        surf(reshape(X, 15, 30));
        hold on
        axis([0 30 0 15 150 300])
        hold off
        pause(0.1);
    end
end

% Conversion 2D -> 1D
function k = c(i, j)
    k = 15*(j-1)+i;
end

% Conversion 1D -> 2D
function [i, j] = b(k)
    i = mod(k - 1, 15)+1;
    j = floor((k - 1)/15)+1;
end