function [] = x1(a, b, N, f0)
    Te = (b-a)/N;
    Fe = 1/Te;
    t=a:Te:b-Te;
    f = -Fe/2:Fe/N:Fe/2-Fe/N;

    x = zeros(N, 1);
    for k=1:N
        x(k) = cos(2*pi*f0*t(k));
    end
    plot(t, x);
    pause();
    
    X = tfour(transpose(x));
    plot(f, X);
    pause();
    
    xinv = tfourinv(X);
    plot(t, xinv);
    pause();
end