package test;

import fr.insalyon.gustatif.metier.modele.Client;
import fr.insalyon.gustatif.metier.modele.Livraison;
import fr.insalyon.gustatif.metier.modele.Produit;
import fr.insalyon.gustatif.metier.modele.Restaurant;
import fr.insalyon.gustatif.metier.service.ServiceMetier;
import java.util.HashMap;

public class CreationLivraison {

    public static void main(String[] args) {
        ServiceMetier service = new ServiceMetier();
        try {
            service.initialiserDonnees();
        } catch (Throwable t) {
            System.out.println("ERREUR : Initialisation impossible.");
        }

        Livraison livraison = null;

        try {
            Client client = service.authentifierClient("philipp.now@yahoo.com", "password");
            Restaurant restaurant = service.listerRestaurants().get(5);
            HashMap<Produit, Long> produits = new HashMap<Produit, Long>();
            produits.put(service.listerProduitsRestaurant(restaurant).get(1), new Long(1));
            produits.put(service.listerProduitsRestaurant(restaurant).get(2), new Long(1));
            produits.put(service.listerProduitsRestaurant(restaurant).get(3), new Long(2));

            livraison = service.commander(client, restaurant, produits);
        } catch (Throwable t) {
            System.out.println("ERREUR : Commande impossible.");
            t.printStackTrace();
        }

        System.out.println(livraison);
        System.out.println("Commande terminée");
    }

}
