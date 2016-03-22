package test;

import fr.insalyon.gustatif.metier.modele.Client;
import fr.insalyon.gustatif.metier.modele.Livraison;
import fr.insalyon.gustatif.metier.modele.Produit;
import fr.insalyon.gustatif.metier.modele.Restaurant;
import fr.insalyon.gustatif.metier.service.ServiceMetier;
import fr.insalyon.gustatif.metier.service.ServiceTechnique;
import java.util.HashMap;
import java.util.logging.Level;
import java.util.logging.Logger;

public class CreationLivraison {

    public static void main(String[] args) {
        ServiceMetier service = new ServiceMetier();
        try {
            service.initialiserDonnees();
        } catch (Throwable ex) {
            Logger.getLogger(CreationLivraison.class.getName()).log(Level.SEVERE, null, ex);
        }

        Client client = new Client("SPARROW", "Jack", "jack.sparrow@tortugua.com", "pirate", "81 Quai Charles de Gaulle, 69006 Lyon");
        client.setCoordonnees(ServiceTechnique.getLatLng(client.getAdresse()));
        Restaurant restaurant = new Restaurant("La Bonne Table", "Restaurant 3 étoiles *** des plus réputés de l'île. Ambiance garantie !", "130 Boulevard du 11 Novembre 1918, 69100 Villeurbanne");
        restaurant.setCoordonnees(ServiceTechnique.getLatLng(restaurant.getAdresse()));
        Produit produit1 = new Produit("Gigot de d'agneau", "Un gigot dans son jus succulent.", 21.6f, 1.2f);
        Produit produit2 = new Produit("Salade nicoise", "Superbe salde fraichement ceuillie accompagnée de tomates.", 8.9f, 0.01f);
        Produit produit3 = new Produit("Tarte groumande", "Une part de tarte au chocolat avec 80% de cacao, acompagnée d'une lime de citron.", 9.99f, 0.158f);
        HashMap<Produit, Long> produits = new HashMap<Produit, Long>();
        produits.put(produit1, new Long(1));
        produits.put(produit2, new Long(1));
        produits.put(produit3, new Long(2));

        Livraison livraison = null;
        try {
            livraison = service.commander(client, restaurant, produits);
            System.out.println(livraison);
        } catch (Throwable t) {
            System.out.println("ERREUR : Commande impossible.");
            t.printStackTrace();
        }

        System.out.println("Commande terminée");
    }

}
