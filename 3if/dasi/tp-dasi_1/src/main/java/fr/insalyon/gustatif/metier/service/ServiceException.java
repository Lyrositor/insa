package fr.insalyon.gustatif.metier.service;

public class ServiceException extends Exception {

    private int numero;
    private String description;

    public static final int ERREUR_CREATION_CLIENT = 1;
    public static final int ERREUR_CREATION_CLIENT_MAIL = 2;
    public static final int ERREUR_INTROUVABLE = 3;
    public static final int ERREUR_MOT_DE_PASSE = 4;

    public ServiceException(int numero, String description) {
        this.numero = numero;
        this.description = description;
    }

    public ServiceException(int numero) {
        this.numero = numero;
        this.description = null;
    }

    public int getNumero() {
        return numero;
    }

    public String getDescription() {
        return description;
    }

    public void setNumero(int numero) {
        this.numero = numero;
    }

    public void setDescription(String description) {
        this.description = description;
    }

}
