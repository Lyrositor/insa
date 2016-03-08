package fr.insalyon.gustatif.metier.modele;

import java.util.Date;
import java.util.HashMap;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.Temporal;

/**
 *
 * @author afavier
 */
public class Livraison {

    @Id
    private Client client = null;
    private Livreur livreur = null;
    @Temporal(javax.persistence.TemporalType.DATE)
    private Date dateCommande = null;
    @Temporal(javax.persistence.TemporalType.DATE)
    private Date dateLivraison = null;

    @ManyToOne
    private HashMap<Produit, Float> produits;

    public Livraison() {
    }
}
