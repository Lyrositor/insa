package fr.insalyon.gustatif.metier.modele;

import javax.persistence.Id;

/**
 *
 * @author afavier
 */
public class Cycliste extends Livreur {

    @Id
    private String email;
    private String motDePasse;
    private String nom;

    public Cycliste() {
    }

    public Cycliste(String email, String motDePasse, String nom) {
        this.email = email;
        this.motDePasse = motDePasse;
        this.nom = nom;
    }

    public String getEmail() {
        return email;
    }

    public String getMotDePasse() {
        return motDePasse;
    }

    public String getNom() {
        return nom;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setMotDePasse(String motDePasse) {
        this.motDePasse = motDePasse;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

}
