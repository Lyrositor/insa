function [] = x5(a, b, N, f0)
    Te = (b-a)/N;
    Fe = 1/Te;
    t = a:Te:b-Te;
    f = -Fe/2:Fe/N:Fe/2-Fe/N;

    x = zeros(N, 1);
    for k=1:N
        x(k) = exp(1i*2*pi*f0*t(k));
    end
    plot3(real(x),imag(x),t);
    pause();
    
    X = tfour(transpose(x));
    plot3(real(X),imag(X),f);
    pause();
    
    xinv = tfourinv(X);
    plot(t, xinv);
    pause();
end