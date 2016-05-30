function [] = TerrainToBlackWhitePng (matrice, output_name)
matrice = (matrice - min(matrice(:))) / ( max(matrice(:)) - min(matrice(:)));
imwrite(uint16(matrice*65535),output_name);
end