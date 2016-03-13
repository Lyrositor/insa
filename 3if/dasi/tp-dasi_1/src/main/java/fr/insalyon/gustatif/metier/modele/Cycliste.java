package fr.insalyon.gustatif.metier.modele;

import java.io.Serializable;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
public class Cycliste extends Livreur implements Serializable {

    @Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    private Long id;
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
                ", capacite=" + getCapacite() +
                ", disponible=" + isDisponible() +
                ", mail=" + mail +
                ", nom=" + nom +
                '}';
    }

}
