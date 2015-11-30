function[] = application_2()

    N = 32768;
    a = -5;
    b = 5;
    f1 = 1/(2*pi);
    f2 = 2400;
    d = 40;
    
    Te = (b-a)/N;
    Fe = 1/Te;
    t=a:Te:b-Te;
    f = -Fe/2:Fe/N:Fe/2-Fe/N;

    x1 = zeros(N, 1);
    x2 = zeros(N, 1);

    for k=1:N
        x1(k) = sin(2*pi*f1*t(k)) + 2*sin(2*pi*(f1 + d)*t(k))+3*sin(2*pi*(f1 + 2*d)*t(k));
        x2(k) = sin(2*pi*f2*t(k)) + 2*sin(2*pi*(f2 + d)*t(k))+3*sin(2*pi*(f2 + 2*d)*t(k));
    end
 
    
    X1 = tfour(transpose(x1));
    X2 = tfour(transpose(x2));

    plot(f, imag(X1), 'b', f, imag(X2), 'r');
    pause();
    
 