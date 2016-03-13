package fr.insalyon.gustatif.metier.modele;

import java.io.Serializable;
import java.util.Date;
import java.util.HashMap;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.OneToOne;
import javax.persistence.Temporal;

@Entity
public class Livraison implements Serializable {

    @Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    private Long id;
    @OneToOne
    private Client client;
    @OneToOne
    private Livreur livreur;
    @Temporal(javax.persistence.TemporalType.DATE)
    private Date dateCommande;
    @Temporal(javax.persistence.TemporalType.DATE)
    private Date dateLivraison;
    @ManyToOne
    private HashMap<Produit, Float> produits;

    public Livraison() {
    }
    
    public Livraison(Client client, Livreur livreur, Date dateCommande, Date dateLivraison, HashMap<Produit, Float> produits) {
        this.client = client;
        this.livreur = livreur;
        this.dateCommande = dateCommande;
        this.dateLivraison = dateLivraison;
        this.produits = produits;
    }
    
    public Client getClient() {
        return client;
    }

    public void setClient(Client client) {
        this.client = client;
    }

    public Livreur getLivreur() {
        return livreur;
    }

    public void setLivreur(Livreur livreur) {
        this.livreur = livreur;
    }

    public Date getDateCommande() {
        return dateCommande;
    }

    public void setDateCommande(Date dateCommande) {
        this.dateCommande = dateCommande;
    }

    public Date getDateLivraison() {
        return dateLivraison;
    }

    public void setDateLivraison(Date dateLivraison) {
        this.dateLivraison = dateLivraison;
    }

    public HashMap<Produit, Float> getProduits() {
        return produits;
    }

    public void setProduits(HashMap<Produit, Float> produits) {
        this.produits = produits;
    }
    
    @Override
    public String toString() {
        return "Livraison{" +
                "id=" + id +
                ", client=" + client +
                ", livreur=" + livreur +
                ", dateCommande=" + dateCommande +
                ", dateLivraison=" + dateLivraison +
                ", produits=" + produits +
                '}';
    }

}
