package fr.insalyon.gustatif.metier.modele;

import java.io.Serializable;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
public class Drone extends Livreur implements Serializable {

    @Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    private Long id;
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
