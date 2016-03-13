package fr.insalyon.gustatif.metier.modele;

import java.util.List;
import javax.persistence.OneToMany;

public abstract class Livreur {

    private boolean disponible;
    private float capacite;
    @OneToMany
    private List<Livraison> livraisons;

    public boolean isDisponible() {
        return disponible;
    }

    public float getCapacite() {
        return capacite;
    }

    public List<Livraison> getLivraisons() {
        return livraisons;
    }

    public void setDisponible(boolean disponible) {
        this.disponible = disponible;
    }

    public void setCapacite(float capacite) {
        this.capacite = capacite;
    }

    public void setLivraisons(List<Livraison> livraisons) {
        this.livraisons = livraisons;
    }

}
