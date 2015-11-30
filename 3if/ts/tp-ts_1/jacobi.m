function X = jacobi(A, B, max_iterations)
    [A_i, A_j] = size(A);
    X = ones(A_j, 1);
    
    for k=1:max_iterations
        Xm = X;
        for i=1:A_j
            X(i) = (B(i) - A(i,:)*Xm)/A(i, i) + Xm(i);
        end
        if max(abs(A*X - B)) <= 10^-7
            k
            break
        end
    end
end