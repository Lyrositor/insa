function [] = x7(a, b, N)
    Te = (b-a)/N;
    Fe = 1/Te;
    t = a:Te:b-Te;
    f = -Fe/2:Fe/N:Fe/2-Fe/N;

    x = zeros(N, 1);
    for k=1:N
        x(k) = exp(-pi*(t(k))^2);
    end
    
    figure(1)
    plot(t, x);
    pause();
    
    X = tfour(transpose(x));
    figure(2)
    plot(f, real(X));
    pause();
    
    xinv = tfourinv(X);
    figure(3)
    plot(t, real(xinv));
    pause();
end