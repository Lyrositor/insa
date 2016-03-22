package fr.insalyon.gustatif.metier.modele;

import com.google.maps.model.LatLng;
import java.io.Serializable;
import java.util.List;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.OneToMany;

@Entity
public abstract class Livreur implements Serializable {

    @Id
    @GeneratedValue
    protected Long id;
    protected float capacite;
    protected boolean disponible = true;
    protected String adresse;
    protected Double longitude;
    protected Double latitude;

    @OneToMany
    protected List<Livraison> livraisons;

    public Long getId() {
        return id;
    }

    public boolean isDisponible() {
        return disponible;
    }

    public float getCapacite() {
        return capacite;
    }

    public String getAdresse() {
        return adresse;
    }

    public Double getLongitude() {
        return longitude;
    }

    public Double getLatitude() {
        return latitude;
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

    public void setAdresse(String adresse) {
        this.adresse = adresse;
    }

    public void setCoordonnees(LatLng latLng) {
        this.longitude = latLng.lng;
        this.latitude = latLng.lat;
    }

    public void setLivraisons(List<Livraison> livraisons) {
        this.livraisons = livraisons;
    }

}
