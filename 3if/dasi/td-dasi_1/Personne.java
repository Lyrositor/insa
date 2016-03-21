package fr.insalyon.dasi.td.jpa;

import com.google.maps.GeoApiContext;
import com.google.maps.GeocodingApi;
import com.google.maps.model.GeocodingResult;
import com.google.maps.model.LatLng;
import java.io.Serializable;
import java.util.Date;
import javax.persistence.*;

@Entity
public class Personne implements Serializable {
    
    @Id
    private String nom;
    private String prenom;
    @Temporal(javax.persistence.TemporalType.DATE)
    private Date dateNaissance;
    private String adresse;
    private String latitude;
    private String longitude;

    public Personne() {
    }

    public Personne(String nom, String prenom, Date dateNaissance, String adresse) {
        this.nom = nom;
        this.prenom = prenom;
        this.dateNaissance = dateNaissance;
        this.adresse = adresse;
    }

    public String getNom() {
        return nom;
    }

    public String getPrenom() {
        return prenom;
    }

    public Date getDateNaissance() {
        return dateNaissance;
    }

    public Integer getAge() {
        return new Date().getYear() - dateNaissance.getYear();
    }

    public String getAdresse() {
        return adresse;
    }

    @Override
    public String toString() {
        return "Personne{" + "nom=" + nom + ", prenom=" + prenom + ", age=" + getAge() + ", adresse=" + adresse + "}";
    }
    
    final static GeoApiContext MON_CONTEXTE_GEOAPI =
        new GeoApiContext().setApiKey("AIzaSyAhf3JleYpal9S-xouJYH8lf7Dvz5Y2Nko");
    
    public static LatLng getLatLng(String adresse) {
    try {
        GeocodingResult[] results =
            GeocodingApi.geocode(MON_CONTEXTE_GEOAPI,adresse).await();
        return results[0].geometry.location;
    } catch (Exception ex) {
        return null;
    }
}
   
}