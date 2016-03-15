package fr.insalyon.gustatif.metier.service;

import com.google.maps.model.LatLng;
import fr.insalyon.gustatif.dao.*;
import fr.insalyon.gustatif.metier.modele.*;
import java.math.BigInteger;
import java.util.Random;
import static fr.insalyon.gustatif.util.GeoTest.getFlightDistanceInKm;
import static fr.insalyon.gustatif.util.GeoTest.getLatLng;
import static fr.insalyon.gustatif.util.GeoTest.getTripDurationByBicycleInMinute;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map.Entry;

public class ServiceMetier {

    private static final ClientDao clientDao = new ClientDao();
    private static final GestionnaireDao gestionnaireDao = new GestionnaireDao();
    private static final LivraisonDao livraisonDao = new LivraisonDao();
    private static final LivreurDao livreurDao = new LivreurDao();
    private static final ProduitDao produitDao = new ProduitDao();
    private static final RestaurantDao restaurantDao = new RestaurantDao();

    private static final String[] NOMS = {
        "MARTIN", "DUPRE", "BERNARD", "DUBOIS", "THOMAS", "ROBERT", "RICHARD",
        "PETIT"
    };
    private static final String[] PRENOMS = {
        "Jean", "Daniel", "Anne", "Marie", "Pierre", "Jullie", "Marc", "Arnaud"
    };
    private static final String[] RUES = {
        "Cours Emile Zola", "rue Galilee", "rue du Marais", "rue du Tonkin"
    };
    private static final int MAX_NUMERO_RUE = 100;
    private static final float MAX_CAPACITE_CYCLISTE = 50.0f;
    private static final float MAX_CAPACITE_DRONE = 20.0f;
    private static final int NUM_CYCLISTES = 40;
    private static final int NUM_DRONES = 10;

    public void initialiserDonnees() throws Throwable {
        // Création des données en dur sur les livreurs et les gestionnaires
        Random r = new Random();
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();
        for (int i = 0; i < NUM_CYCLISTES; i++) {
            String nom = NOMS[r.nextInt(NOMS.length)];
            String prenom = PRENOMS[r.nextInt(PRENOMS.length)];
            Cycliste cycliste = new Cycliste(
                    nom, prenom,
                    prenom.toLowerCase() + '.' + nom.toLowerCase() + "@gustatif.com",
                    new BigInteger(130, r).toString(32),
                    (r.nextInt(MAX_NUMERO_RUE) + 1) + ' ' + RUES[r.nextInt(RUES.length)],
                    r.nextFloat() * MAX_CAPACITE_CYCLISTE, true
            );
            livreurDao.create(cycliste);
        }
        JpaUtil.validerTransaction();
        JpaUtil.fermerEntityManager();
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

    public Livraison commander(Client client, Restaurant restaurant, HashMap<Produit, Long> produits) throws ServiceException, Throwable {
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();

        // Calcul des localisation
        if (client.getLatitude() == null) {
            throw new ServiceException(12, "Latitude de l'adresse cliente non définie.");
        }
        if (client.getLongitude() == null) {
            throw new ServiceException(13, "Longitude de l'adresse cliente non définie.");
        }
        LatLng localisationClient = new LatLng(client.getLatitude(), client.getLongitude());

        if (restaurant.getLatitude() == null) {
            throw new ServiceException(14, "Latitude de l'adresse du restaurant non définie.");
        }
        if (restaurant.getLongitude() == null) {
            throw new ServiceException(15, "Longitude de l'adresse du restaurant non définie.");
        }
        LatLng localisationRestaurant = new LatLng(restaurant.getLatitude(), restaurant.getLongitude());

        Double distanceRestaurantClient = getFlightDistanceInKm(localisationRestaurant, localisationClient);

        // Calcul du poids de la commande
        Float poidsCommande = 0f;
        for (Entry<Produit, Long> entry : produits.entrySet()) {
            Produit produit = entry.getKey();
            //Long id = entry.getValue();
            poidsCommande += produit.getPoids();
        }

        // Liste des livreurs disponibles et capables de supporter la charge
        List<Livreur> listeLivreurs = null;
        for (Livreur livreur : livreurDao.findAll()) {
            if (livreur.isDisponible() && poidsCommande <= livreur.getCapacite()) {
                listeLivreurs.add(livreur);
            }
        }
        if (listeLivreurs == null) {
            throw new ServiceException(11, "Aucun livreur n'est disponible ou ne possède une capacité de charge suffisante pour le moment. Merci de commander plus tard.");
        }

        // Sélection du livreur le plus proche
        Livreur livreurSelection = null;
        Double dureeMini = Double.MAX_VALUE;
        for (Livreur livreur : listeLivreurs) {
            Double duree = Double.MAX_VALUE;
            if (livreur instanceof Cycliste) {
                duree = getTripDurationByBicycleInMinute(getLatLng(livreur.getAdresse()), localisationClient, localisationRestaurant);
            } else if (livreur instanceof Drone) {
                Double distance = getFlightDistanceInKm(getLatLng(livreur.getAdresse()), localisationRestaurant);
                distance += distanceRestaurantClient;
                duree = (distance / ((Drone) livreur).getVitesseMoyenne()) * 60;
            }
            if (dureeMini > duree) {
                dureeMini = duree;
                livreurSelection = livreur;
            }
        }

        Livraison livraison = new Livraison(client, livreurSelection, new Date(), null, produits);
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
