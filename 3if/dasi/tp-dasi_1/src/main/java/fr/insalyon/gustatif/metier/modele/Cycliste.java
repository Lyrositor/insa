package fr.insalyon.gustatif.metier.modele;

import javax.persistence.Entity;

@Entity
public class Cycliste extends Livreur {

    private String nom;
    private String prenom;
    private String mail;
    private String motDePasse;

    public Cycliste() {
    }

    public Cycliste(
            String nom, String prenom, String mail, String motDePasse,
            float capacite, boolean disponible, String adresse
    ) {
        this.nom = nom;
        this.prenom = prenom;
        this.mail = mail;
        this.motDePasse = motDePasse;
        this.adresse = adresse;
        this.disponible = disponible;
        this.capacite = capacite;
    }

    public String getNom() {
        return nom;
    }

    public String getPrenom() {
        return prenom;
    }

    public String getMail() {
        return mail;
    }

    public String getMotDePasse() {
        return motDePasse;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public void setPrenom(String prenom) {
        this.prenom = prenom;
    }

    public void setMail(String mail) {
        this.mail = mail;
    }

    public void setMotDePasse(String motDePasse) {
        this.motDePasse = motDePasse;
    }

    @Override
    public String toString() {
        return "Cycliste{" +
                "id=" + id +
                ", nom=" + nom +
                ", prenom=" + prenom +
                ", mail=" + mail +
                ", motDePasse=" + motDePasse +
                ", capacite=" + capacite +
                ", disponible=" + disponible +
                ", adresse=" + adresse +
                ", longitude=" + longitude +
                ", latitude=" + latitude +
                '}';
    }

}
