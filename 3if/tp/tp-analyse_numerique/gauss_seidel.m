function X = gauss_seidel(A, B, max_iterations)
    [A_i, A_j] = size(A);
    X = ones(A_j, 1);
    Xm = X;
    
    for k=1:max_iterations
        for i=1:A_j
            X(i) = (B(i) - A(i,1:i-1)*X(1:i-1) - A(i,i+1:A_j)*Xm(i+1:A_j))/A(i, i);
        end
        if max(abs(A*X - B)) <= 10^-7
            k
            break
        end
        Xm = X;
    end
end