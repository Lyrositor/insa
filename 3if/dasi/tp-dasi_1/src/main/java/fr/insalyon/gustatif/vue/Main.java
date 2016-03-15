package fr.insalyon.gustatif.vue;

import fr.insalyon.gustatif.dao.ClientDao;
import fr.insalyon.gustatif.dao.GestionnaireDao;
import fr.insalyon.gustatif.dao.JpaUtil;
import fr.insalyon.gustatif.dao.LivraisonDao;
import fr.insalyon.gustatif.dao.LivreurDao;
import fr.insalyon.gustatif.dao.ProduitDao;
import fr.insalyon.gustatif.dao.RestaurantDao;

public class Main {

    public static void main(String[] args) {

        ClientDao clientDao = new ClientDao();
        GestionnaireDao gestionnaireDao = new GestionnaireDao();
        LivraisonDao livraisonDao = new LivraisonDao();
        LivreurDao livreurDao = new LivreurDao();
        ProduitDao produitDao = new ProduitDao();
        RestaurantDao restaurantDao = new RestaurantDao();

        JpaUtil.creerEntityManager();

        JpaUtil.ouvrirTransaction();
        JpaUtil.validerTransaction();

        JpaUtil.fermerEntityManager();

    }
}
