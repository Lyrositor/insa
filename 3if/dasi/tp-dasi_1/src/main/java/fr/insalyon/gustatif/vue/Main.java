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

    public static void main(String[] args) {
        ServiceMetier service = new ServiceMetier();
        try {
            //service.initialiserDonnees();
        } catch (Throwable t) {
            t.printStackTrace();
            System.err.println("ERREUR: Échec lors de l'initialisation.");
            return;
        }

        List<Restaurant> restaurants;
        List<Livreur> livreurs;
        try {
            restaurants = service.listerRestaurants();
            livreurs = service.listerLivreurs();
        } catch (Throwable t) {
            System.err.println("ERREUR: Échec lors du chargement des données.");
            return;
        }
        Client client;
        Restaurant restaurant;
        HashMap<Produit, Long> produits;
        String mail;
        String motDePasse;
        Cycliste cycliste;

        List<Integer> options = Arrays.asList(1, 2, 3, 4, 5, 6);
        afficherBienvenue();
        while (true) {
            Integer choix = Saisie.lireInteger("Choix : ", options);
            client = null;
            restaurant = null;
            produits = new HashMap<>();
            mail = null;
            motDePasse = null;
            switch (choix) {
                case 1:
                    System.out.println(restaurants);
                    break;
                case 2:
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
                    System.out.println(service.listerProduitsRestaurant(restaurant));
                    break;
                case 3:
                    System.out.println("Connectez-vous avec votre compte client :");
                    mail = Saisie.lireChaine("Mail : ");
                    motDePasse = Saisie.lireChaine("Mot de passe : ");
                    try {
                        client = service.authentifierClient(mail, motDePasse);
                    } catch (ServiceException e) {
                        System.out.println("ERREUR : Erreur d'authentification.");
                        break;
                    }
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
                    System.out.println("Choisissez vos produits :");
                    for (Produit p : service.listerProduitsRestaurant(restaurant)) {
                        int qte = Saisie.lireInteger(p.getDenomination() + " (" + p.getDescription() + ") : ");
                        if (qte > 0)
                            produits.put(p, new Long(qte));
                    }
                    try {
                        service.commander(client, restaurant, produits);
                    } catch (ServiceException e) {
                        System.out.println("ERREUR : Échec de la commande.");
                        break;
                    }
                    System.out.println("Commande effectuée.");
                    break;
                case 4:
                    System.out.println("Connectez-vous avec votre compte cycliste :");
                    mail = Saisie.lireChaine("Mail : ");
                    motDePasse = Saisie.lireChaine("Mot de passe : ");
                    try {
                        cycliste = service.authentifierCycliste(mail, motDePasse);
                    } catch (ServiceException e) {
                        System.out.println("ERREUR : erreur d'authentification.");
                        break;
                    }
                    List<Livraison> livraisons = cycliste.getLivraisons();
                    System.out.println("Livraisons (historique) : " + livraisons);
                    System.out.println("Clôturation de la livraison en cours...");
                    Livraison livraison = null;
                    for (Livraison l : livraisons)
                        if (l.getDateLivraison() == null) {
                            livraison = l;
                            break;
                        }
                    if (livraison != null) {
                        try {
                            service.cloturerLivraison(livraison, new Date());
                            System.out.println("Livraison clôturée : " + livraison);
                        } catch (ServiceException e) {
                            System.err.println("ERREUR : Échec lors de la clôturation.");
                        }
                    } else
                        System.out.println("ERREUR : Aucune livraison en cours.");
                    break;
                case 5:
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
                case 6:
                    System.out.println(livreurs);
                    break;
            }
        }
    }

    private static void afficherBienvenue() {
        System.out.println(
                " _______           _______ _________ _______ _________ _ _________ _______ \n" +
                "(  ____ \\|\\     /|(  ____ \\\\__   __/(  ___  )\\__   __/( )\\__   __/(  ____ \\\n" +
                "| (    \\/| )   ( || (    \\/   ) (   | (   ) |   ) (   |/    ) (   | (    \\/\n" +
                "| |      | |   | || (_____    | |   | (___) |   | |         | |   | (__    \n" +
                "| | ____ | |   | |(_____  )   | |   |  ___  |   | |         | |   |  __)   \n" +
                "| | \\_  )| |   | |      ) |   | |   | (   ) |   | |         | |   | (      \n" +
                "| (___) || (___) |/\\____) |   | |   | )   ( |   | |      ___) (___| )      \n" +
                "(_______)(_______)\\_______)   )_(   |/     \\|   )_(      \\_______/|/       \n");
        System.out.println("Bienvenue à Gustat'IF Enterprise Edition 2017 (TM).");
        System.out.println("Choisissez votre action :");
        System.out.println("1) Lister les restaurants");
        System.out.println("2) Lister les produits d'un restaurant");
        System.out.println("3) Créer une livraison");
        System.out.println("4) Cloturer une livraison");
        System.out.println("5) Inscrire un client");
        System.out.println("6) Lister les livreurs");
    }
}
