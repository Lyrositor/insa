function GenererImage(terrain)
    terrain = double(terrain);
    mini = min(min(terrain));
    maxi = max(max(terrain));
    
    t = 65535*(terrain-mini)/(maxi-mini);
    ut = uint16(t);
    
    imwrite(ut, 'terrain.png');
end