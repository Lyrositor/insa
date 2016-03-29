package fr.insalyon.gustatif.vue;

import fr.insalyon.gustatif.metier.modele.*;
import fr.insalyon.gustatif.metier.service.ServiceException;
import fr.insalyon.gustatif.metier.service.ServiceMetier;
import fr.insalyon.gustatif.util.Saisie;
import java.util.Arrays;
import java.util.Date;
import java.util.HashMap;
import java.util.List;

public class Main {

    private static final String INTRO =
            " _______           _______ _________ _______ _________ _ _________ _______ \n" +
            "(  ____ \\|\\     /|(  ____ \\\\__   __/(  ___  )\\__   __/( )\\__   __/(  ____ \\\n" +
            "| (    \\/| )   ( || (    \\/   ) (   | (   ) |   ) (   |/    ) (   | (    \\/\n" +
            "| |      | |   | || (_____    | |   | (___) |   | |         | |   | (__    \n" +
            "| | ____ | |   | |(_____  )   | |   |  ___  |   | |         | |   |  __)   \n" +
            "| | \\_  )| |   | |      ) |   | |   | (   ) |   | |         | |   | (      \n" +
            "| (___) || (___) |/\\____) |   | |   | )   ( |   | |      ___) (___| )      \n" +
            "(_______)(_______)\\_______)   )_(   |/     \\|   )_(      \\_______/|/       \n\n" +
            "Bienvenue à GUSTAT'IF Enterprise Edition 2017 (TM).";
    private static final String CHOIX =
            "Choisissez votre action :\n" +
            "0) Initialiser les données\n" +
            "1) Lister les restaurants\n" +
            "2) Lister les produits d'un restaurant\n" +
            "3) Créer une livraison\n" +
            "4) Cloturer une livraison (cycliste)\n" +
            "5) Cloturer une livraison (gestionnaire)\n" +
            "6) Inscrire un client\n" +
            "7) Lister les livreurs\n";

    public static void main(String[] args) {
        ServiceMetier service = new ServiceMetier();

        Client client;
        Cycliste cycliste;
        Livraison livraison;
        List<Livraison> livraisons;
        String mail;
        String motDePasse;
        List<Produit> produits;
        HashMap<Produit, Long> produitsCommande;
        Restaurant restaurant;
        List<Integer> options = Arrays.asList(0, 1, 2, 3, 4, 5, 6, 7);

        List<Restaurant> restaurants;
        List<Livreur> livreurs;
        try {
            restaurants = service.listerRestaurants();
        } catch (ServiceException e) {
            System.err.println("ERREUR: Échec lors du chargement des données.");
            return;
        }

        System.out.println(INTRO);
        while (true) {
            System.out.println(CHOIX);
            Integer choix = Saisie.lireInteger("Choix : ", options);
            client = null;
            livraison = null;
            restaurant = null;
            produits = null;
            produitsCommande = new HashMap<>();
            mail = null;
            motDePasse = null;
            switch (choix) {
                // Initialiser les données
                case 0:
                    try {
                        service.initialiserDonnees();
                        restaurants = service.listerRestaurants();
                        livreurs = service.listerLivreurs();
                    } catch (ServiceException e) {
                        System.out.println("ERREUR : Échec de l'initialisation.");
                    }
                    break;

                // Lister les restaurants
                case 1:
                    // Affichage des restaurants
                    System.out.println("Restaurants :");
                    for (Restaurant r : restaurants)
                        System.out.println("\t" + r);
                    break;

                // Lister les produits d'un restaurant
                case 2:
                    // Choix du restaurant
                    do {
                        long restaurantId = Saisie.lireInteger("ID du restaurant : ");
                        for (Restaurant r : restaurants)
                            if (r.getId() == restaurantId) {
                                restaurant = r;
                                break;
                            }
                        if (restaurant == null)
                            System.out.println("ERREUR : Ce restaurant n'existe pas.");
                    } while (restaurant == null);

                    // Affichage des produits
                    System.out.println("Produits :");
                    for (Produit p : service.listerProduitsRestaurant(restaurant))
                        System.out.println("\t" + p);
                    break;

                // Créer une livraison
                case 3:
                    // Authentification
                    System.out.println("Connectez-vous avec votre compte client.");
                    mail = Saisie.lireChaine("\tMail : ");
                    motDePasse = Saisie.lireChaine("\tMot de passe : ");
                    try {
                        client = service.authentifierClient(mail, motDePasse);
                    } catch (ServiceException e) {
                        System.out.println("ERREUR : Erreur d'authentification.");
                        break;
                    }

                    // Choix du restaurant
                    do {
                        long restaurantId = Saisie.lireInteger("ID du restaurant : ").longValue();
                        for (Restaurant r : restaurants)
                            if (r.getId() == restaurantId) {
                                restaurant = r;
                                break;
                            }
                        if (restaurant == null)
                            System.out.println("ERREUR : Ce restaurant n'existe pas.");
                    } while (restaurant == null);

                    // Choix des produits
                    System.out.println("Choisissez vos produits :");
                    for (Produit p : service.listerProduitsRestaurant(restaurant)) {
                        int qte = Saisie.lireInteger("\t" + p.getDenomination() + " (" + p.getDescription() + ") : ");
                        if (qte > 0)
                            produitsCommande.put(p, new Long(qte));
                    }

                    // Commande
                    try {
                        service.commander(client, restaurant, produitsCommande);
                        livreurs = service.listerLivreurs();
                    } catch (ServiceException e) {
                        System.out.println("ERREUR : Échec de la commande.");
                        break;
                    }
                    System.out.println("Commande effectuée.");
                    break;

                // Cloturer une livraison (cycliste)
                case 4:
                    // Authentification
                    System.out.println("Connectez-vous avec votre compte cycliste.");
                    mail = Saisie.lireChaine("\tMail : ");
                    motDePasse = Saisie.lireChaine("\tMot de passe : ");
                    try {
                        cycliste = service.authentifierCycliste(mail, motDePasse);
                    } catch (ServiceException e) {
                        System.out.println("ERREUR : Erreur d'authentification.");
                        break;
                    }

                    // Affichage de l'historique des livraisons
                    livraisons = cycliste.getLivraisons();
                    for (Livraison l : livraisons)
                        System.out.println("\t" + l);

                    // Clôturation de la livraison en cours
                    System.out.println("Clôturation de la livraison en cours...");
                    for (Livraison l : livraisons)
                        if (l.getDateLivraison() == null) {
                            livraison = l;
                            break;
                        }
                    if (livraison != null) {
                        try {
                            service.cloturerLivraison(livraison, new Date());
                            livreurs = service.listerLivreurs();
                            System.out.println("Livraison clôturée : " + livraison);
                        } catch (ServiceException e) {
                            System.err.println("ERREUR : Échec lors de la clôturation.");
                        }
                    } else
                        System.out.println("ERREUR : Aucune livraison en cours.");
                    break;

                // Cloturer une livraison (gestionnaire)
                case 5:
                    // Authentification
                    System.out.println("Connectez-vous avec votre compte gestionnaire.");
                    mail = Saisie.lireChaine("\tMail : ");
                    motDePasse = Saisie.lireChaine("\tMot de passe : ");
                    Gestionnaire gestionnaire;
                    try {
                        gestionnaire = service.authentifierGestionnaire(mail, motDePasse);
                    } catch (ServiceException e) {
                        System.out.println("ERREUR : Erreur d'authentification.");
                        break;
                    }

                    // Choisir le livreur
                    try {
                        livreurs = service.listerLivreurs();
                    } catch (ServiceException e) {
                        System.err.println("ERREUR: Échec lors du chargement des données.");
                        return;
                    }
                    Livreur livreur = null;
                    do {
                        long livreurId = Saisie.lireInteger("ID du livreur : ").longValue();
                        for (Livreur l : livreurs)
                            if (l.getId() == livreurId) {
                                livreur = l;
                                break;
                            }
                        if (livreur == null)
                            System.out.println("ERREUR : Ce livreur n'existe pas.");
                    } while (livreur == null);

                    // Affichage de l'historique des livraisons
                    livraisons = livreur.getLivraisons();
                    for (Livraison l : livraisons)
                        System.out.println("\t" + l);

                    // Clôturation de la livraison en cours
                    System.out.println("Clôturation de la livraison en cours...");
                    for (Livraison l : livraisons)
                        if (l.getDateLivraison() == null) {
                            livraison = l;
                            break;
                        }
                    if (livraison != null) {
                        try {
                            service.cloturerLivraison(livraison, new Date());
                            livreurs = service.listerLivreurs();
                            System.out.println("Livraison clôturée : " + livraison);
                        } catch (ServiceException e) {
                            System.err.println("ERREUR : Échec lors de la clôturation.");
                        }
                    } else
                        System.out.println("ERREUR : Aucune livraison en cours.");
                    break;

                // Inscrire un client
                case 6:
                    String nom = Saisie.lireChaine("Nom : ");
                    String prenom = Saisie.lireChaine("Prénom : ");
                    mail = Saisie.lireChaine("Mail : ");
                    motDePasse = Saisie.lireChaine("Mot de passe : ");
                    String adresse = Saisie.lireChaine("Adresse : ");
                    client = new Client(nom, prenom, mail, motDePasse, adresse);
                    try {
                        service.inscrireClient(client);
                        System.out.println("Création réussie : " + client);
                    } catch (ServiceException e) {
                        System.out.println("ERREUR : Impossible de créer client.");
                    }
                    break;

                // Lister les livreurs
                case 7:
                    try {
                        livreurs = service.listerLivreurs();
                    } catch (ServiceException e) {
                        System.err.println("ERREUR: Échec lors du chargement des données.");
                        return;
                    }
                    
                    System.out.println("Livreurs :");
                    for (Livreur l : livreurs)
                        System.out.println("\t" + l);
                    break;
            }
        }
    }

}
