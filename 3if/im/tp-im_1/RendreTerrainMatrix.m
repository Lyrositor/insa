function RendreTerrainMatrix(terrain, texture, outfile, origin, target)
w = (target - origin);
w = w/norm(w);
u = (cross([0; 0; 1], w));
u = u/norm(u);
v = (cross(w, u));
matrix = zeros(4);
matrix(1:3,1) = u;
matrix(1:3,2) = v;
matrix(1:3,3) = w;
matrix(1:3,4) = origin;
matrix(4,4) = 1;
matrix = matrix';
repertoire = '\\servif-home\fic_eleves\Espace Pedagogique\3IF\Modeles et Outils Mathematiques\Images fondements\image\Mitsuba';
cmd = strcat('"', repertoire, '\mitsuba" -Dhfile=', terrain, ...
    ' -Dtfile=', texture, ...
    ' -Dmatrix="', sprintf('%f ', matrix(:)), ...
    '" -o ', outfile, ' texture-matrix.xml' ...
);
disp(cmd);
system(cmd);
end
