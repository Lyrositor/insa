package fr.insalyon.ihm.controleur.gestionnaires;

import fr.insalyon.ihm.controleur.exceptions.RequeteException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.http.HttpServletRequest;
import metier.modele.Adherent;
import metier.service.ServiceMetier;

public class GestionListerDemandes implements GestionnaireRequete {

    @Override
    public Object traiterRequete(HttpServletRequest requete)
            throws RequeteException {
        Adherent adherent = (Adherent) requete.getSession().getAttribute("adherent");

        try {
            return ServiceMetier.listerDemandes(adherent);
        } catch (Throwable t) {
            Logger.getLogger(getClass().getName()).log(Level.SEVERE, null, t);
        }

        throw new RequeteException("erreur", "Liste des demandes impossible.");
    }

}