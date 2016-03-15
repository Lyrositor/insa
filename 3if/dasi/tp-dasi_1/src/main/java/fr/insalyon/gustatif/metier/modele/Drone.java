package fr.insalyon.gustatif.metier.modele;

import java.io.Serializable;
import javax.persistence.Entity;

@Entity
public class Drone extends Livreur implements Serializable {

    private float vitesseMoyenne;

    public Drone() {
    }

    public Drone(float vitesseMoyenne, float capacite) {
        this.vitesseMoyenne = vitesseMoyenne;
        this.capacite = capacite;
    }

    public float getVitesseMoyenne() {
        return vitesseMoyenne;
    }

    public void setVitesseMoyenne(float vitesseMoyenne) {
        this.vitesseMoyenne = vitesseMoyenne;
    }

    @Override
    public String toString() {
        return "Drone{" +
                "id=" + id +
                ", vitesseMoyenne=" + vitesseMoyenne +
                ", capacite=" + capacite +
                ", disponible=" + disponible +
                ", adresse=" + adresse +
                ", longitude=" + longitude +
                ", latitude=" + latitude +
                '}';
    }

}
