package fr.insalyon.ihm.controleur.exceptions;

public class RequeteException extends Exception {

    private final String statut;

    public RequeteException(String statut, String message) {
        super(message);
        this.statut = statut;
    }

    public String getStatut() {
        return statut;
    }

}
