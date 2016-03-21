package fr.insalyon.gustatif.metier.modele;

import java.io.Serializable;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;

@Entity
public class Gestionnaire implements Serializable {

    @Id @GeneratedValue
    private Long id;
    private String mail;
    private String motDePasse;

    public Gestionnaire() {
    }

    public Gestionnaire(String mail, String motDePasse) {
        this.mail = mail;
        this.motDePasse = motDePasse;
    }

    public String getMail() {
        return mail;
    }

    public String getMotDePasse() {
        return motDePasse;
    }

    public void setMail(String mail) {
        this.mail = mail;
    }

    public void setMotDePasse(String motDePasse) {
        this.motDePasse = motDePasse;
    }

    @Override
    public String toString() {
        return "Gestionnaire{" +
                "id=" + id +
                ", mail=" + mail +
                '}';
    }

}
