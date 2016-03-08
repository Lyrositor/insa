package fr.insalyon.gustatif.metier.modele;

import java.util.List;
import javax.persistence.Id;
import javax.persistence.OneToMany;

/**
 *
 * @author afavier
 */
public abstract class Livreur {

    @Id
    private boolean disponible;
    private float capacite;

    @OneToMany
    private List<Livraison> livraisons;

    public Livreur() {
    }

    public Livreur(boolean disponible, float capacite, List<Livraison> livraisons) {
        this.disponible = disponible;
        this.capacite = capacite;
        this.livraisons = livraisons;
    }

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
