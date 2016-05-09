function test

[im,] = imread('C:\Users\Public\Pictures\Sample Pictures\Koala.jpg');

mapndg = ([0:255]'/255)*[1 1 1];

imndg = 0.3*im(:,:,1) + 0.59*im(:,:,2) + 0.11*im(:,:,3);

figure(1)
image(imndg)
colormap(mapndg)

imndg = double(imndg);
[NL,NC] = size(imndg);

% histogramme
histo = zeros(1, 256);
for L = 1:NL,
    for C = 1:NC,
        histo(imndg(L, C) + 1) = histo(imndg(L, C) + 1) + 1;
    end
end
figure(2)
plot(histo)

% histogramme cumulé
histocum = zeros(1, 256);
histocum(1) = histo(1);
for n=2:256,
    histocum(n) = histocum(n - 1) + histo(n);
end
figure(3)
plot(histocum)

% seuillage
seuil = 128;
imseuil = zeros(NL, NC);

for L= 1:NL,
    for C = 1:NC,
        if imndg(L, C) < seuil
            imseuil(L, C) = 0;
        else
            imseuil(L, C) = 255;
        end
    end
end

figure(4)
image(imseuil)
colormap(mapndg)

% contraste
K = 10;
moy = mean(mean(imndg));

imcont = K * (imndg - moy) + moy;
figure(5)
image(imcont)
colormap(mapndg)

% convolution
masque = ones(3);
K = 9;
offset = 0;

masque = [0 1 0;1 -4 1;0 1 0];
K = 1;
offset = 128;

imconv = zeros(NL, NC);
for L=2:NL-1,
    for C=2:NC-1,
        imconv(L, C) = sum(sum(imndg(L-1:L+1,C-1:C+1).*masque))/K + offset;
    end
end

figure(6)
image(imconv)
colormap(mapndg)

end