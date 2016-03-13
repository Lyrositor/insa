package fr.insalyon.gustatif.metier.service;

import fr.insalyon.gustatif.metier.modele.*;
import java.util.Date;
import java.util.List;

public class ServiceMetier {

    public void initialiserService() {
        
    }
    
    public boolean creerClient(Client client) {
        return false;
    }
    
    public boolean authentifier(String email, String motdePasse) {
        return false;
    }
    
    public void commander(Livraison livraison) {
    }
    
    public List<Restaurant> listerRestaurants() {
        return null;
    }
    
    public List<Plat> listerPlatsRestaurant(Restaurant restaurant) {
        return null;
    }
    
    public List<Livreur> listerLivreurs() {
        return null;
    }
    
    public List<Client> listerClients() {
        return null;
    }
    
    public void cloturerLivraison(Livraison livraison, Date dateLivraison) {
    }

}
