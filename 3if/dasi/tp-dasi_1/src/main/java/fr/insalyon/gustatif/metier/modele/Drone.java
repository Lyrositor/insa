package fr.insalyon.gustatif.metier.modele;

import javax.persistence.Entity;

@Entity
public class Drone extends Livreur {

    private float vitesseMoyenne;

    public Drone() {
    }

    public Drone(
            float vitesseMoyenne, float capacite, boolean disponible,
            String adresse) {
        this.vitesseMoyenne = vitesseMoyenne;
        this.adresse = adresse;
        this.capacite = capacite;
        this.disponible = disponible;
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
