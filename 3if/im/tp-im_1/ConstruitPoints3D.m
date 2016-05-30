function [ points ] = ConstruitPoints3D (terrain, xmin, xmax, ymin, ymax )
[h, l] = size(terrain);
points = zeros(h, l, 3);
points(:,:,1) = repmat(double(0:l-1)/double(l) * (xmax-xmin)+xmin, h, 1);
points(:,:,2) = repmat((double(0:h-1)/double(h) * (ymax-ymin)+ymin)', 1, l);
points(:,:,3) = terrain;
end

