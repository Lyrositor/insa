package test;

import fr.insalyon.gustatif.metier.modele.Client;
import fr.insalyon.gustatif.metier.modele.Livraison;
import fr.insalyon.gustatif.metier.modele.Produit;
import fr.insalyon.gustatif.metier.modele.Restaurant;
import fr.insalyon.gustatif.metier.service.ServiceMetier;
import java.util.HashMap;

public class CreationLivraison {

    private static final String EMAIL = "vincent.duraf@gmail.com";
    private static final String MOT_DE_PASSE = "password";
    private static final int RESTAURANT = 5;
    private static final int[] PRODUITS = {1, 2, 3};

    /* Attention : le fichier data.sql dans ressrouces doit être chargé avant exécution ! */
    public static void main(String[] args) {
        try {
            ServiceMetier service = new ServiceMetier();
            service.initialiserDonnees();

            Livraison livraison = null;

            Client client = service.authentifierClient(EMAIL, MOT_DE_PASSE);
            Restaurant restaurant = service.listerRestaurants().get(RESTAURANT);
            HashMap<Produit, Long> produits = new HashMap<Produit, Long>();
            produits.put(service.listerProduitsRestaurant(restaurant).get(PRODUITS[0]), new Long(1));
            produits.put(service.listerProduitsRestaurant(restaurant).get(PRODUITS[1]), new Long(1));
            produits.put(service.listerProduitsRestaurant(restaurant).get(PRODUITS[2]), new Long(2));

            livraison = service.commander(client, restaurant, produits);

            System.out.println("Commande terminée avec succès :");
            System.out.println(livraison);

        } catch (Throwable t) {
            System.out.println("ERREUR : Commande impossible.");
            t.printStackTrace();
        }
    }

}
