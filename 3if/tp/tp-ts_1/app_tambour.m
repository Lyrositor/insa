function [MAX_v, MAX_V, MIN_v, MIN_V] = app_tambour
    TAILLE = 150;

    % Construction de A
    A = zeros(TAILLE);
    for k=1:TAILLE
        [i, j] = b(k);
        if i == 1 || i == 10 || j == 1 || j == 15 || (any(i == 1:6) && any(j == 7:9))
            A(k, k) = 1;
            continue
        end
        A(k, k) = -4;
        A(k, c(i - 1, j)) = 1;
        A(k, c(i + 1, j)) = 1;
        A(k, c(i, j - 1)) = 1;
        A(k, c(i, j + 1)) = 1;
    end
        
    % Construction de Z
    Z = A^(-1);
    
    [MAX_v, MAX_V] = deflation_wielandt(A, 10, 1E-9);
    for i=1:10
        surf(reshape(MAX_V(:,i), 10, 15))
        pause(1)
    end
    
    [MIN_z, MIN_V] = deflation_wielandt(Z, 10, 1E-9);
    MIN_v = MIN_z.^-1;
    for i=1:10
        surf(reshape(MIN_V(:,i), 10, 15))
        pause(1)
    end
end

% Conversion 2D -> 1D
function k = c(i, j)
    k = 10*(j-1)+i;
end

% Conversion 1D -> 2D
function [i, j] = b(k)
    i = mod(k - 1, 10)+1;
    j = floor((k - 1)/10)+1;
end