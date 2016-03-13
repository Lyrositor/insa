package fr.insalyon.gustatif.vue;

import fr.insalyon.gustatif.dao.ClientDao;
import fr.insalyon.gustatif.dao.JpaUtil;
import fr.insalyon.gustatif.dao.ProduitDao;
import fr.insalyon.gustatif.dao.RestaurantDao;
import fr.insalyon.gustatif.metier.modele.Client;
import fr.insalyon.gustatif.metier.modele.Produit;
import fr.insalyon.gustatif.metier.modele.Restaurant;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Main {

    public static void main(String[] args) {

        ClientDao clientDao = new ClientDao();
        ProduitDao produitDao = new ProduitDao();
        RestaurantDao restaurantDao = new RestaurantDao();

        JpaUtil.creerEntityManager();

        JpaUtil.ouvrirTransaction();
        JpaUtil.validerTransaction();

        JpaUtil.fermerEntityManager();

    }
}
