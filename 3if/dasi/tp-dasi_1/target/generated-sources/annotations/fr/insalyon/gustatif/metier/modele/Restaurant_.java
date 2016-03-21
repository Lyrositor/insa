package fr.insalyon.gustatif.metier.modele;

import fr.insalyon.gustatif.metier.modele.Produit;
import javax.annotation.Generated;
import javax.persistence.metamodel.ListAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2016-03-08T15:32:52")
@StaticMetamodel(Restaurant.class)
public class Restaurant_ { 

    public static volatile SingularAttribute<Restaurant, Long> id;
    public static volatile SingularAttribute<Restaurant, String> adresse;
    public static volatile ListAttribute<Restaurant, Produit> produits;
    public static volatile SingularAttribute<Restaurant, String> description;
    public static volatile SingularAttribute<Restaurant, Double> longitude;
    public static volatile SingularAttribute<Restaurant, Double> latitude;
    public static volatile SingularAttribute<Restaurant, String> denomination;

}