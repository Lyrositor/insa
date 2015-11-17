function [] = x4(a, b, N)
    Te = (b-a)/N;
    Fe = 1/Te;
    t = a:Te:b-Te;
    f = -Fe/2:Fe/N:Fe/2-Fe/N;

    x = zeros(N, 1);
    x(16380) = 1;
    plot(t, x);
    pause();
    
    X = tfour(transpose(x));
    plot(f, X);
    pause();
    
    xinv = tfourinv(X);
    plot(t, xinv);
    pause();
end