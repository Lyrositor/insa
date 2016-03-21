function [] = app_repartition_temperature()
    % Construction de A
    A = zeros(450);
    [A_i, A_y] = size(A);
    for k=1:A_i
        [i, j] = b(k);
        if (i == 1 || i == 15) || (i == 8 && any(j == 16:18)) || (any(i == 4:12) && any(j == 21:22))
            A(k, k) = 1;
        else
            A(k, k) = -4;
            
            % Voisins ordinaires
            A(k, c(i - 1, j)) = 1;
            A(k, c(i + 1, j)) = 1;
            if j ~= 1
                A(k, c(i, j - 1)) = 1;
            else
                A(k, c(i, 12)) = 1;
            end
            if j ~= 30
                A(k, c(i, j + 1)) = 1;
            else
                A(k, c(i, 12)) = 1;
            end
            
            % Voisins du pli
            if j == 12
                A(k, k) = -6;
                A(k, c(i, 1)) = 1;
                A(k, c(i, 30)) = 1;
            end
        end
    end
    
    % Construction de B
    B = zeros(450, 1);
    for j=16:18
        B(c(8, j)) = 100;
    end
    for j=1:30
        B(c(1, j)) = 50;
        B(c(15, j)) = 50;
    end
    for i=4:12
        for j=21:22
            B(c(i, j)) = 10;
        end
    end
    
    % Affichage de la repartition
    surf(reshape(jacobi(A, B, 100000), 15, 30));
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