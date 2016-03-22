package fr.insalyon.gustatif.vue;

import fr.insalyon.gustatif.metier.service.ServiceMetier;

public class Main {

    public static void main(String[] args) {
        ServiceMetier service = new ServiceMetier();
        try {
            service.initialiserDonnees();
        } catch (Throwable t) {
            System.err.println("ERREUR: Échec lors de l'initialisation.");
            return;
        }
        System.err.println("INFO: Initialisation terminée.");
    }
}
