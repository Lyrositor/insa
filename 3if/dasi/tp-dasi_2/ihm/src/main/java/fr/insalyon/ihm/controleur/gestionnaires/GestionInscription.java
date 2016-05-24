package fr.insalyon.ihm.controleur.gestionnaires;

import fr.insalyon.ihm.controleur.exceptions.RequeteException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.http.HttpServletRequest;
import metier.modele.Adherent;
import metier.service.ServiceMetier;

public class GestionInscription implements GestionnaireRequete {

    @Override
    public Object traiterRequete(HttpServletRequest requete)
            throws RequeteException {
        Adherent adherent;
        try {
            adherent = ServiceMetier.inscrireAdherent(
                    requete.getParameter("nom"),
                    requete.getParameter("prenom"),
                    requete.getParameter("adresse"),
                    requete.getParameter("email")
            );
        } catch (Throwable ex) {
            Logger.getLogger(getClass().getName()).log(Level.SEVERE, null, ex);
            return null;
        }

        // Vérifier si l'adhérent n'a pas été inscrit
        if (adherent == null)
            throw new RequeteException("erreur", "Inscription impossible");
        return adherent;
    }

}
