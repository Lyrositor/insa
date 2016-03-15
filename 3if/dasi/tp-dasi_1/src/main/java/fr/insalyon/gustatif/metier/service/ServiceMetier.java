package fr.insalyon.gustatif.metier.service;

import fr.insalyon.gustatif.dao.*;
import fr.insalyon.gustatif.metier.modele.*;
import java.util.Date;
import java.util.HashMap;
import java.util.List;

public class ServiceMetier {

    private static ClientDao clientDao = new ClientDao();
    private static GestionnaireDao gestionnaireDao = new GestionnaireDao();
    private static LivraisonDao livraisonDao = new LivraisonDao();
    private static LivreurDao livreurDao = new LivreurDao();
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

    public Livraison commander(Client client, HashMap<Produit, Long> produits) throws Throwable {
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();

        List<Livreur> listeLivreur = livreurDao.findAll();

        Livraison livraison = new Livraison(client, null, new Date(), null, produits);
        livraisonDao.create(livraison);

        JpaUtil.validerTransaction();
        return livraison;
    }

    public List<Restaurant> listerRestaurants() throws Throwable {
        JpaUtil.creerEntityManager();

        List<Restaurant> listeRestaurants = restaurantDao.findAll();
        return listeRestaurants;
    }

    public List<Produit> listerProduitsRestaurant(Restaurant restaurant) {
        JpaUtil.creerEntityManager();

        List<Produit> listeProduits = restaurant.getProduits();
        return listeProduits;
    }

    public List<Livreur> listerLivreurs() throws Throwable {
        JpaUtil.creerEntityManager();

        List<Livreur> listeLivreurs = livreurDao.findAll();
        return listeLivreurs;
    }

    public void cloturerLivraison(Livraison livraison, Date dateLivraison) throws ServiceException, Throwable {
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();

        if (dateLivraison.before(livraison.getDateCommande())) {
            throw new ServiceException(10, "La date de livraison ne peut être inférieure à la date de commande.");
        }
        livraison.setDateLivraison(dateLivraison);
        livraisonDao.update(livraison);

        JpaUtil.validerTransaction();
    }

}
