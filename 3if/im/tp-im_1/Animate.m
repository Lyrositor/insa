function Animate(  )
% Creation du décor
Terrain
terrain = GenererTerrain(Terr, 6, 50, 0.5);
TerrainToBlackWhitePng(terrain, 'terrain.png');
points = ConstruitPoints3D(terrain, -600, 600, -450, 450);
normales = ConstruitNormales(points);

for i = 0:40
    TextureToColorPng(Ombrage(terrain, 100, 'colorramp.png', normales, [cos(i/10) 0 sin(i/10)]), 'texture.png');
    RenderTerrain('terrain.png', 'texture.png', strcat(' render/',sprintf('%d',i),'.png'), [750 600 800], [0 0 0]);
end

end

