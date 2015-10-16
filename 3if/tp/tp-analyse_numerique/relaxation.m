function X = relaxation(A, B, max_iterations)
    [A_i, A_j] = size(A);
    U = triu(A,1);
    D = diag(diag(A));
    L = tril(A, -1) ;
    X = ones(A_j, 1);
    
    calcPI = @(w) (D + w*L)\(((1 - w)*D - w*U));
    w = 1;
    for w_temp=10^-2:2-10^-2
        if max(eig(calcPI(w_temp))) < max(eig(calcPI(w)))
            w = w_temp;
        end
    end
    PI = calcPI(w);

    for k=1:max_iterations
        Xm = X;
        X = PI*Xm + (D + w*L)\(w*B);
        if max(abs(A*X - B)) <= 10^-7
            k
            break
        end
    end
end

