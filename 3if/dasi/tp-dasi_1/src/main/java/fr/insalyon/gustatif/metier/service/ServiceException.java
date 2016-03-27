package fr.insalyon.gustatif.metier.service;

public class ServiceException extends Exception {

    private int numero;

    public static final int ERREUR_INITIALISATION = 0;

    public static final int ERREUR_CREATION_CLIENT = 1;
    public static final int ERREUR_CREATION_CLIENT_MAIL = 2;
    public static final int ERREUR_INTROUVABLE = 3;
    public static final int ERREUR_MOT_DE_PASSE = 4;

    public static final int ERREUR_CLIENT_LATITUDE = 5;
    public static final int ERREUR_CLIENT_LONGITUDE = 6;
    public static final int ERREUR_RESTAURANT_LATITUDE = 7;
    public static final int ERREUR_RESTAURANT_LONGITUDE = 8;
    public static final int ERREUR_LIVREUR_LISTE = 9;
    public static final int ERREUR_LIVREUR_SELECTION = 10;
    public static final int ERREUR_LIVRAISON_CREATE = 11;
    public static final int ERREUR_LIVREUR_UPDATE = 12;

    public static final int ERREUR_LIVRAISON_DATE = 13;
    public static final int ERREUR_LIVRAISON_UPDATE = 14;

    public static final int ERREUR_LISTE_RESTAURANTS = 15;
    public static final int ERREUR_LISTE_LIVREURS = 15;

    public ServiceException(int numero) {
        this.numero = numero;
    }

    public int getNumero() {
        return numero;
    }

    public void setNumero(int numero) {
        this.numero = numero;
    }

}
