/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package metier.modele;

/**
 *
 * @author ovicente
 */
import java.io.Serializable;
import java.util.Date;
import java.util.List;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Inheritance;
import javax.persistence.InheritanceType;
import javax.persistence.OneToMany;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

@Entity
@Inheritance (strategy = InheritanceType.JOINED)
public class Evenement implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    protected Integer id;
    
    @Temporal(TemporalType.DATE)
    protected Date date;
    
    protected Activite activite;
    
    protected Lieu lieu;
    
    @OneToMany(mappedBy="evenement")
    protected List<Demande> demandes;

    public Evenement() {
    }
    
    public Evenement(Date date, Activite activite, List<Demande> demandes) {
        this.date = date;
        this.activite = activite;
        this.lieu = null;
        this.demandes = demandes;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public Activite getActivite() {
        return activite;
    }

    public void setActivite(Activite activite) {
        this.activite = activite;
    }

    public Lieu getLieu() {
        return lieu;
    }

    public void setLieu(Lieu lieu) {
        this.lieu = lieu;
    }

    public List<Demande> getDemandes() {
        return demandes;
    }

    public void setDemandes(List<Demande> demandes) {
        this.demandes = demandes;
    }

    @Override
    public String toString() {
        return "Evenement{" + "id=" + id + ", date=" + date + ", activite=" + activite + ", lieu=" + lieu + ", demandes=" + demandes + '}';
    }
    
}