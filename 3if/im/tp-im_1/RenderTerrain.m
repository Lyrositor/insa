function [  ] = RenderTerrain ( terrain, texture, outfile, origin, target )

repertoire = '\\servif-home\fic_eleves\Espace Pedagogique\3IF\Modeles et Outils Mathematiques\Images fondements\image\Mitsuba';
cmd = strcat('"',repertoire,'\mitsuba" -Dhfile=',terrain,' -Dtfile=',texture,' -Dorigin="',sprintf('%f ',origin), '" -Dtarget="',sprintf('%f ',target), '" -o ',outfile,' texture-lookat.xml');
disp(cmd);
system(cmd);

end

