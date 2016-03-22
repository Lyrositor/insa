package fr.insalyon.gustatif.metier.service;

import com.google.maps.model.LatLng;
import fr.insalyon.gustatif.dao.*;
import fr.insalyon.gustatif.metier.modele.*;
import java.io.IOException;
import java.math.BigInteger;
import java.util.Random;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map.Entry;
import java.util.logging.Level;
import java.util.logging.Logger;

public class ServiceMetier {

    private static final ClientDao CLIENT_DAO = new ClientDao();
    private static final GestionnaireDao GESTIONNAIRE_DAO = new GestionnaireDao();
    private static final LivraisonDao LIVRAISON_DAO = new LivraisonDao();
    private static final LivreurDao LIVREUR_DAO = new LivreurDao();
    private static final ProduitDao PRODUIT_DAO = new ProduitDao();
    private static final RestaurantDao RESTAURANT_DAO = new RestaurantDao();

    private static final String[] NOMS = {
        "MARTIN", "DUPRE", "BERNARD", "DUBOIS", "THOMAS", "ROBERT", "RICHARD",
        "PETIT"
    };
    private static final String[] PRENOMS = {
        "Jean", "Daniel", "Anne", "Marie", "Pierre", "Jullie", "Marc", "Arnaud"
    };
    private static final String[] RUES = {
        "Cours Emile Zola, 69100 Villeurbanne",
        "rue Galilée, 69100 Villeurbanne",
        "rue du Marais, 69100 Villeurbanne",
        "rue du Tonkin, 69100 Villeurbanne"
    };
    private static final int MAX_NUMERO_RUE = 100;
    private static final float MAX_CAPACITE_CYCLISTE = 50000.0f;
    private static final float MAX_CAPACITE_DRONE = 20000.0f;
    private static final float MAX_VITESSE_MOYENNE = 50.0f;
    private static final int NUM_CYCLISTES = 40;
    private static final int NUM_DRONES = 10;
    private static final int NUM_GESTIONNAIRES = 3;

    public void initialiserDonnees() throws Throwable {
        Random r = new Random();
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();

        // Création en dur des cyclistes
        for (int i = 0; i < NUM_CYCLISTES; i++) {
            String nom = NOMS[r.nextInt(NOMS.length)];
            String prenom = PRENOMS[r.nextInt(PRENOMS.length)];
            String adresse = (r.nextInt(MAX_NUMERO_RUE) + 1) + " " + RUES[r.nextInt(RUES.length)];
            LatLng coordonnees = ServiceTechnique.getLatLng(adresse);
            Cycliste cycliste = new Cycliste(
                    nom, prenom,
                    prenom.toLowerCase() + '.' + nom.toLowerCase() + "@gustatif.fr",
                    new BigInteger(130, r).toString(32),
                    r.nextFloat() * MAX_CAPACITE_CYCLISTE, true,
                    (r.nextInt(MAX_NUMERO_RUE) + 1) + " " + RUES[r.nextInt(RUES.length)]
            );
            cycliste.setCoordonnees(coordonnees);
            LIVREUR_DAO.create(cycliste);
        }

        // Création en dur des drones
        for (int i = 0; i < NUM_DRONES; i++) {
            Drone drone = new Drone(
                    r.nextFloat() * MAX_VITESSE_MOYENNE,
                    r.nextFloat() * MAX_CAPACITE_DRONE, true,
                    (r.nextInt(MAX_NUMERO_RUE) + 1) + " " + RUES[r.nextInt(RUES.length)]
            );
            LIVREUR_DAO.create(drone);
        }

        // Création en dur des gestionnaires
        for (int i = 0; i < NUM_GESTIONNAIRES; i++) {
            String nom = NOMS[r.nextInt(NOMS.length)];
            String prenom = PRENOMS[r.nextInt(PRENOMS.length)];
            Gestionnaire gestionnaire = new Gestionnaire(
                    prenom.toLowerCase() + '.' + nom.toLowerCase() + "@gustatif.fr",
                    new BigInteger(130, r).toString(32)
            );
            GESTIONNAIRE_DAO.create(gestionnaire);
        }

        JpaUtil.validerTransaction();
        JpaUtil.fermerEntityManager();
    }

    public void inscrireClient(Client client) throws ServiceException {
        // Géolocaliser le client en cours d'insccription.
        LatLng coordonnees = ServiceTechnique.getLatLng(client.getAdresse());
        client.setCoordonnees(coordonnees);

        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();

        // Vérifier qu'il n'y pas d'autres clients avec le même mail
        try {
            Client c = CLIENT_DAO.findByMail(client.getMail());
            JpaUtil.fermerEntityManager();
            throw new ServiceException(ServiceException.ERREUR_CREATION_CLIENT_MAIL);
        } catch (Throwable t) {
        }

        // Ajouter le client.
        try {
            CLIENT_DAO.create(client);
        } catch (Throwable t) {
            JpaUtil.fermerEntityManager();
            throw new ServiceException(ServiceException.ERREUR_CREATION_CLIENT);
        }

        JpaUtil.validerTransaction();
        JpaUtil.fermerEntityManager();
    }

    public Client authentifierClient(String mail, String motDePasse) throws ServiceException {
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();

        // Trouver un client avec l'adresse mail correspondante
        Client client = null;
        try {
            client = CLIENT_DAO.findByMail(mail);
        } catch (Throwable t) {
            JpaUtil.fermerEntityManager();
            throw new ServiceException(ServiceException.ERREUR_INTROUVABLE);
        }
        JpaUtil.fermerEntityManager();

        // Vérifier le mot de passe.
        if (!motDePasse.equals(client.getMotDePasse())) {
            throw new ServiceException(ServiceException.ERREUR_MOT_DE_PASSE);
        }

        return client;
    }

    public Cycliste authentifierCycliste(String mail, String motDePasse) throws ServiceException {
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();

        // Trouver un client avec l'adresse mail correspondante
        Cycliste cycliste = null;
        try {
            cycliste = (Cycliste) LIVREUR_DAO.findByMail(mail);
        } catch (Throwable t) {
            JpaUtil.fermerEntityManager();
            throw new ServiceException(ServiceException.ERREUR_INTROUVABLE);
        }
        JpaUtil.fermerEntityManager();

        // Vérifier le mot de passe.
        if (!motDePasse.equals(cycliste.getMotDePasse())) {
            throw new ServiceException(ServiceException.ERREUR_MOT_DE_PASSE);
        }

        return cycliste;
    }

    public Gestionnaire authentifierGestionnaire(String mail, String motDePasse) throws ServiceException {
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();

        // Trouver un client avec l'adresse mail correspondante
        Gestionnaire gestionnaire = null;
        try {
            gestionnaire = GESTIONNAIRE_DAO.findByMail(mail);
        } catch (Throwable t) {
            JpaUtil.fermerEntityManager();
            throw new ServiceException(ServiceException.ERREUR_INTROUVABLE);
        }
        JpaUtil.fermerEntityManager();

        // Vérifier le mot de passe.
        if (!motDePasse.equals(gestionnaire.getMotDePasse())) {
            throw new ServiceException(ServiceException.ERREUR_MOT_DE_PASSE);
        }

        return gestionnaire;
    }

    public Livraison commander(Client client, Restaurant restaurant, HashMap<Produit, Long> produits) throws ServiceException {
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();

        // Calcul des localisation
        if (client.getLatitude() == null) {
            JpaUtil.fermerEntityManager();
            throw new ServiceException(ServiceException.ERREUR_CLIENT_LATITUDE);
        }
        if (client.getLongitude() == null) {
            JpaUtil.fermerEntityManager();
            throw new ServiceException(ServiceException.ERREUR_CLIENT_LONGITUDE);
        }
        LatLng localisationClient = new LatLng(client.getLatitude(), client.getLongitude());

        if (restaurant.getLatitude() == null) {
            JpaUtil.fermerEntityManager();
            throw new ServiceException(ServiceException.ERREUR_RESTAURANT_LATITUDE);
        }
        if (restaurant.getLongitude() == null) {
            JpaUtil.fermerEntityManager();
            throw new ServiceException(ServiceException.ERREUR_RESTAURANT_LONGITUDE);
        }
        LatLng localisationRestaurant = new LatLng(restaurant.getLatitude(), restaurant.getLongitude());

        Double distanceRestaurantClient = ServiceTechnique.getFlightDistanceInKm(localisationRestaurant, localisationClient);

        // Calcul du poids de la commande
        Float poidsCommande = 0f;
        for (Entry<Produit, Long> entry : produits.entrySet()) {
            Produit produit = entry.getKey();
            //Long id = entry.getValue();
            poidsCommande += produit.getPoids();
        }

        // Liste des livreurs disponibles et capables de supporter la charge
        List<Livreur> listeLivreurs;
        try {
            listeLivreurs = LIVREUR_DAO.findAllAvalaibleWithCapacity(poidsCommande);
        } catch (Throwable ex) {
            throw new ServiceException(ServiceException.ERREUR_LIVREUR_LISTE);
        }

        // Sélection du livreur le plus proche
        Livreur livreurSelection = null;
        Double dureeMini = Double.MAX_VALUE;
        for (Livreur livreur : listeLivreurs) {
            Double duree = Double.MAX_VALUE;
            if (livreur instanceof Cycliste) {
                duree = ServiceTechnique.getTripDurationByBicycleInMinute(ServiceTechnique.getLatLng(livreur.getAdresse()), localisationClient, localisationRestaurant);
            } else if (livreur instanceof Drone) {
                Double distance = ServiceTechnique.getFlightDistanceInKm(ServiceTechnique.getLatLng(livreur.getAdresse()), localisationRestaurant);
                distance += distanceRestaurantClient;
                duree = (distance / ((Drone) livreur).getVitesseMoyenne()) * 60;
            }
            if (dureeMini > duree) {
                dureeMini = duree;
                livreurSelection = livreur;
            }
        }

        if (livreurSelection == null) {
            JpaUtil.fermerEntityManager();
            throw new ServiceException(ServiceException.ERREUR_LIVREUR_SELECTION);
        }

        /* DEMO */
        System.out.println("Attente de l'utilisateur... Appuyer sur [Entrée] pour continuer.");
        try {
            System.in.read();
        } catch (Exception e) {
        }
        /* --- */

        Livraison livraison = new Livraison(client, livreurSelection, new Date(), null, produits);
        try {
            LIVRAISON_DAO.create(livraison);
        } catch (Throwable ex) {
            throw new ServiceException(ServiceException.ERREUR_LIVRAISON_CREATE);
        }
        livreurSelection.setDisponible(false);
        try {
            LIVREUR_DAO.update(livreurSelection);
        } catch (Throwable ex) {
            throw new ServiceException(ServiceException.ERREUR_LIVREUR_UPDATE);
        }

        JpaUtil.validerTransaction();
        JpaUtil.fermerEntityManager();
        return livraison;
    }

    public List<Restaurant> listerRestaurants() throws Throwable {
        JpaUtil.creerEntityManager();

        List<Restaurant> listeRestaurants = RESTAURANT_DAO.findAll();

        JpaUtil.fermerEntityManager();
        return listeRestaurants;
    }

    public List<Produit> listerProduitsRestaurant(Restaurant restaurant) {
        JpaUtil.creerEntityManager();

        List<Produit> listeProduits = restaurant.getProduits();

        JpaUtil.fermerEntityManager();
        return listeProduits;
    }

    public List<Livreur> listerLivreurs() throws Throwable {
        JpaUtil.creerEntityManager();

        List<Livreur> listeLivreurs = LIVREUR_DAO.findAll();

        JpaUtil.fermerEntityManager();
        return listeLivreurs;
    }

    public void cloturerLivraison(Livraison livraison, Date dateLivraison) throws ServiceException {
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();

        if (dateLivraison.before(livraison.getDateCommande())) {
            throw new ServiceException(ServiceException.ERREUR_LIVRAISON_DATE);
        }
        livraison.setDateLivraison(dateLivraison);
        Livreur livreur = livraison.getLivreur();
        livreur.setDisponible(true);
        try {
            LIVRAISON_DAO.update(livraison);
        } catch (Throwable ex) {
            throw new ServiceException(ServiceException.ERREUR_LIVRAISON_UPDATE);
        }
        try {
            LIVREUR_DAO.update(livreur);
        } catch (Throwable ex) {
            throw new ServiceException(ServiceException.ERREUR_LIVREUR_UPDATE);
        }

        JpaUtil.validerTransaction();
        JpaUtil.fermerEntityManager();
    }

}
