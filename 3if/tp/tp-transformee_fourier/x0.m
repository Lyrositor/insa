function [] = x0(a, b, N)
    Te = (b-a)/N;
    Fe = 1/Te;
    t=a:Te:b-Te;
    f = -Fe/2:Fe/N:Fe/2-Fe/N;

    C = 13;
    x = ones(N, 1) * C;
    plot(t, x);
    pause();
    
    X = tfour(transpose(x));
    plot(f, X);
    pause();
    
    x2 = tfourinv(X);
    plot(t, x2);
    pause();
end