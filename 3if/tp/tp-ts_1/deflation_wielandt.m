function [Lv, LV] = deflation_wielandt(A, n, l)
    [A_i, A_j] = size(A);
    Lv = zeros(1, n);
    LV = zeros(A_j, n);
    B = A;
    
    [v, V] = puissance_iteree(B, l);
    [v, U] = puissance_iteree(B', l);
    
    Lv(1) = v;
    LV(:,1) = V;
    
    for i=2:n
        B = B - v*(V*U')/(U'*V);
        
        [v, V] = puissance_iteree(B, l);
        [v, U] = puissance_iteree(B', l);
        
        Lv(i) = v;
        LV(:,i) = V;
    end
end