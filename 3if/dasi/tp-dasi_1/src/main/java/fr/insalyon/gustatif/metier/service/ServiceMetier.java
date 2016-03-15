package fr.insalyon.gustatif.metier.service;

import fr.insalyon.gustatif.dao.*;
import fr.insalyon.gustatif.metier.modele.*;
import java.util.Date;
import java.util.HashMap;
import java.util.List;

public class ServiceMetier {

    private static ClientDao clientDao = new ClientDao();
    private static CyclisteDao cyclisteDao = new CyclisteDao();
    private static DroneDao droneDao = new DroneDao();
    private static GestionnaireDao gestionnaireDao = new GestionnaireDao();
    private static LivraisonDao livraisonDao = new LivraisonDao();
    private static ProduitDao produitDao = new ProduitDao();
    private static RestaurantDao restaurantDao = new RestaurantDao();

    public void initialiserDonnees() {
        // Chargement des données d'un fichier SQL
        // Création en dur des données
    }

    public void inscrireClient(Client client) {
    }

    public Client authentifierClient(String mail, String motdePasse) {
        return null;
    }

    public Cycliste authentifierCycliste(String mail, String motdePasse) {
        return null;
    }

    public Gestionnaire authentifierGestionnaire(String mail, String motdePasse) {
        return null;
    }

    public Livraison commander(Client client, HashMap<Produit, Long> produits) {
        return null;
    }

    public List<Restaurant> listerRestaurants() throws Throwable {
        RestaurantDao restaurantDao = new RestaurantDao();
        List<Restaurant> listeRestaurants = restaurantDao.findAll();
        return listeRestaurants;
    }

    public List<Produit> listerProduitsRestaurant(Restaurant restaurant) {
        return null;
    }

    public List<Livreur> listerLivreurs() {
        /*CyclisteDao cyclisteDao = new CyclisteDao();
         DroneDao droneDao = new DroneDao();
         List<Livreur> listeLivreurs = null;
         try {
         listeLivreurs = cyclisteDao.findAll();
         } catch (Throwable ex) {
         Logger.getLogger(ServiceMetier.class.getName()).log(Level.SEVERE, null, ex);
         }*/
        return null;
    }

    public void cloturerLivraison(Livraison livraison, Date dateLivraison) {
    }

}
