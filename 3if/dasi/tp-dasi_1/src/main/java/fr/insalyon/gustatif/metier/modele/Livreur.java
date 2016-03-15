package fr.insalyon.gustatif.metier.modele;

import java.util.List;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.OneToMany;

@Entity
public abstract class Livreur {

    @Id @GeneratedValue
    protected Long id;
    protected boolean disponible;
    protected float capacite;
    @OneToMany
    protected List<Livraison> livraisons;

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
