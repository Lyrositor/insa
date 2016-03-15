package fr.insalyon.gustatif.metier.modele;

import javax.persistence.Entity;

@Entity
public class Drone extends Livreur {

    private float vitesseMoyenne;

    public Drone() {
    }

    public Drone(float vitesseMoyenne) {
        this.vitesseMoyenne = vitesseMoyenne;
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
                ", capacite=" + getCapacite() +
                ", disponible=" + isDisponible() +
                ", vitesseMoyenne=" + vitesseMoyenne +
                '}';
    }

}
