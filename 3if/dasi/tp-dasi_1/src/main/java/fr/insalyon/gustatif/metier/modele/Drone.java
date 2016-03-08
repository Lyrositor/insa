package fr.insalyon.gustatif.metier.modele;

import javax.persistence.Id;

/**
 *
 * @author afavier
 */
public class Drone extends Livreur {

    @Id
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

}
