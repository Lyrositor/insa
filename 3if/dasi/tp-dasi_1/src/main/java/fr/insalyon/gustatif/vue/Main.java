package fr.insalyon.gustatif.vue;

import fr.insalyon.gustatif.dao.ClientDao;
import fr.insalyon.gustatif.dao.CyclisteDao;
import fr.insalyon.gustatif.dao.DroneDao;
import fr.insalyon.gustatif.dao.GestionnaireDao;
import fr.insalyon.gustatif.dao.JpaUtil;
import fr.insalyon.gustatif.dao.LivraisonDao;
import fr.insalyon.gustatif.dao.ProduitDao;
import fr.insalyon.gustatif.dao.RestaurantDao;

public class Main {

    public static void main(String[] args) {

        ClientDao clientDao = new ClientDao();
        CyclisteDao cyclisteDao = new CyclisteDao();
        DroneDao droneDao = new DroneDao();
        GestionnaireDao gestionnaireDao = new GestionnaireDao();
        LivraisonDao livraisonDao = new LivraisonDao();
        ProduitDao produitDao = new ProduitDao();
        RestaurantDao restaurantDao = new RestaurantDao();

        JpaUtil.creerEntityManager();

        JpaUtil.ouvrirTransaction();
        JpaUtil.validerTransaction();

        JpaUtil.fermerEntityManager();

    }
}
