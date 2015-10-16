function [ S ] = app_image(M, r, l)
    [A_i, A_j] = size(A);
    S = zeros(A_j, r);
    [Lv, LV] = deflation_wielandt(M, r, l);
    for k=1:r
        s = sqrt(Lv(k))
    end
end

