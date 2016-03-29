package fr.insalyon.gustatif.vue;

import fr.insalyon.gustatif.metier.modele.Livraison;
import fr.insalyon.gustatif.metier.modele.Livreur;
import fr.insalyon.gustatif.metier.service.ServiceMetier;
import fr.insalyon.gustatif.util.Saisie;
import java.util.Date;

public class ClotureLivraison {

    /* Attention : le fichier data.sql dans ressources doit être chargé avant exécution ! */
    public static void main(String[] args) {
        try {
            ServiceMetier service = new ServiceMetier();
            service.initialiserDonnees();

            boolean continuer = true;
            do {
                System.out.println(" --- Cloture de commande --- ");
                System.out.println("1. Numéro / id du livreur");
                System.out.println("2. Numéro / id de la livraison");

                switch (Saisie.lireInteger("Votre choix ? : ")) {
                    case 1:
                        System.out.println(" - Livreur - ");
                        int idLivreur = Saisie.lireInteger("Numéro / id du livreur : ");

                        Livreur livreur = service.trouverLivreur(new Long(idLivreur));
                        if (livreur != null) {
                            if (!livreur.getLivraisons().isEmpty()) {
                                continuer = false;

                                for (Livraison livraison : livreur.getLivraisons()) {
                                    if (livraison.getDateLivraison() == null) {
                                        service.cloturerLivraison(livraison, new Date());
                                        return;
                                    }
                                }
                            } else {
                                System.out.println("Erreur : Pas de livraison pour ce livreur [getLivraison() = null]");
                            }
                        } else {
                            System.out.println("Erreur : Livreur non trouvé [livreur = null]");
                        }
                        break;

                    case 2:
                        System.out.println(" - Livraison - ");
                        int idLivraison = Saisie.lireInteger("Numéro / id de la livraison : ");

                        Livraison livraison = service.trouverLivraison(new Long(idLivraison));
                        if (livraison != null) {
                            continuer = false;

                            service.cloturerLivraison(livraison, new Date());
                            return;
                        } else {
                            System.out.println("Erreur : Livraison non trouvé [livraison = null]");
                        }
                        break;

                    default:
                        System.out.println("Choix incorrect. Merci de recommencer");
                        break;
                }
            } while (continuer);
        } catch (Throwable ex) {
            ex.printStackTrace();
        }
    }
}
