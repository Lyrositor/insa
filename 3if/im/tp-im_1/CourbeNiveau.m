function texture = CourbeNiveau(terrain,inter)

texture = (floor((mod(terrain,inter)+inter*0.1)/inter) );% +...
           %floor((inter -mod(terrain,inter) + inter*0.05)/inter)...
          %)/2 ;
truetexture (:,:,1) = texture;
truetexture (:,:,2) = texture;
truetexture (:,:,3) = texture;
texture = floor(255*(1-truetexture));

end