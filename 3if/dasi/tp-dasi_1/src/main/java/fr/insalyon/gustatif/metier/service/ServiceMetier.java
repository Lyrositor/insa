package fr.insalyon.gustatif.metier.service;

import fr.insalyon.gustatif.dao.ClientDao;
import fr.insalyon.gustatif.dao.JpaUtil;
import fr.insalyon.gustatif.dao.RestaurantDao;
import fr.insalyon.gustatif.metier.modele.*;
import java.util.Date;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

public class ServiceMetier {

    public void initialiserService() {
        JpaUtil.creerEntityManager();
    }

    public boolean creerClient(Client client) {
        return false;
    }

    public boolean authentifier(String mail, String motdePasse) {
        /*// Recherche parmis les clients
         List<Client> listeClients = listerClients();
         for (Client client : listeClients) {
         if (client.getMail().equals(mail) && client.getMotDePasse().equals(motdePasse)) {
         return true;
         }
         }
         // Recherche parmis les cyclistes
         List<Cycliste> listeCyclistes = listerCyclistes();
         for (Cycliste cycliste : listeCyclistes) {
         if (cycliste.getMail().equals(email) && cycliste.getMotDePasse().equals(motdePasse)) {
         return true;
         }
         }*/
        return false;
    }

    public void commander(Livraison livraison) {
    }

    public List<Restaurant> listerRestaurants() {
        RestaurantDao restaurantDao = new RestaurantDao();
        List<Restaurant> listeRestaurants = null;
        try {
            listeRestaurants = restaurantDao.findAll();
        } catch (Throwable ex) {
            Logger.getLogger(ServiceMetier.class.getName()).log(Level.SEVERE, null, ex);
        }
        return listeRestaurants;
    }

    public List<Plat> listerPlatsRestaurant(Restaurant restaurant) {
        return null;
    }

    public List<Livreur> listerLivreurs() {
        /*CyclisteDao cyclisteDao = new CyclisteDao();
         DroneDao droneDao = new DroneDao();
         List<Livreur> listeLivreurs = null;
         try {
         listeLivreurs = cyclisteDao.findAll();
         } catch (Throwable ex) {
         Logger.getLogger(ServiceMetier.class.getName()).log(Level.SEVERE, null, ex);
         }*/
        return null;
    }

    public List<Client> listerClients() {
        ClientDao clientDao = new ClientDao();
        List<Client> listeClients = null;
        try {
            listeClients = clientDao.findAll();
        } catch (Throwable ex) {
            Logger.getLogger(ServiceMetier.class.getName()).log(Level.SEVERE, null, ex);
        }
        return listeClients;
    }

    public void cloturerLivraison(Livraison livraison, Date dateLivraison) {
    }

}
