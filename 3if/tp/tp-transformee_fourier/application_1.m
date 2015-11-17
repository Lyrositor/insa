function[] = application_1()
    a = -5;
    b = 5;
    N = 32768;
    %x0(a, b, N);
    x1(a, b, N, 10);
    %x1(a, b, N, 50.75);
    %x2(a, b, N, 10);
    %x2(a, b, N, 50.75);
    %x3(a, b, N, 30);
    %x4(a, b, N);
    %x5(a, b, N, 10);
    %x5(a, b, N, 50.75);
    %x6(a, b, N, 0.5);
    %x6_periodique(a, b, N, 0.5);
    %x7(a, b, N);
end