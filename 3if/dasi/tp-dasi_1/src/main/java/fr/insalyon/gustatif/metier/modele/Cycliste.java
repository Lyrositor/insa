package fr.insalyon.gustatif.metier.modele;

import javax.persistence.Entity;

@Entity
public class Cycliste extends Livreur {

    private String mail;
    private String motDePasse;
    private String nom;

    public Cycliste() {
    }

    public Cycliste(String mail, String motDePasse, String nom) {
        this.mail = mail;
        this.motDePasse = motDePasse;
        this.nom = nom;
    }

    public String getMail() {
        return mail;
    }

    public String getMotDePasse() {
        return motDePasse;
    }

    public String getNom() {
        return nom;
    }

    public void setMail(String mail) {
        this.mail = mail;
    }

    public void setMotDePasse(String motDePasse) {
        this.motDePasse = motDePasse;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    @Override
    public String toString() {
        return "Cycliste{" +
                "id=" + id +
                ", capacite=" + capacite +
                ", disponible=" + disponible +
                ", mail=" + mail +
                ", nom=" + nom +
                '}';
    }

}
