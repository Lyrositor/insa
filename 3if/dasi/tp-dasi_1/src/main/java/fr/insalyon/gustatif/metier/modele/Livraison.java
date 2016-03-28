package fr.insalyon.gustatif.metier.modele;

import java.io.Serializable;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import javax.persistence.ElementCollection;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.Temporal;
import static javax.persistence.TemporalType.DATE;

@Entity
public class Livraison implements Serializable {

    @Id @GeneratedValue
    private Long id;
    @ManyToOne
    private Client client;
    @ManyToOne
    private Livreur livreur;
    @Temporal(DATE)
    private Date dateCommande;
    @Temporal(DATE)
    private Date dateLivraison = null;
    @ElementCollection
    private Map<Produit, Long> produits;

    public Livraison() {
    }

    public Livraison(Client client, Livreur livreur, Date dateCommande, Date dateLivraison, Map<Produit, Long> produits) {
        this.client = client;
        this.livreur = livreur;
        this.dateCommande = dateCommande;
        this.dateLivraison = dateLivraison;
        this.produits = produits;
        if (!this.livreur.getLivraisons().contains(this))
            this.livreur.ajouterLivraison(this);
    }

    public Long getId() {
        return id;
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
        if (!livreur.getLivraisons().contains(this))
            livreur.ajouterLivraison(this);
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

    public Map<Produit, Long> getProduits() {
        return produits;
    }

    public void setProduits(HashMap<Produit, Long> produits) {
        this.produits = produits;
    }

    @Override
    public String toString() {
        return "Livraison{"
                + "id=" + id
                + ", client=" + client
                + ", livreur=" + livreur
                + ", dateCommande=" + dateCommande
                + ", dateLivraison=" + dateLivraison
                + ", produits=" + produits
                + '}';
    }

}
