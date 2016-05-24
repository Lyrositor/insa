package fr.insalyon.ihm.controleur.gestionnaires;

import fr.insalyon.ihm.controleur.exceptions.RequeteException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.http.HttpServletRequest;
import metier.modele.Adherent;
import metier.modele.Demande;
import metier.service.ServiceMetier;

public class GestionGetDemande implements GestionnaireRequete {

    @Override
    public Object traiterRequete(HttpServletRequest requete)
            throws RequeteException {
        int demandeId = Integer.parseInt(requete.getParameter("demande"));
        Adherent adherent = (Adherent) requete.getSession().getAttribute("adherent");

        try {
            for (Demande demande : ServiceMetier.listerDemandes(adherent))
                if (demande.getId() == demandeId)
                    return demande;
        } catch (Throwable t) {
            Logger.getLogger(getClass().getName()).log(Level.SEVERE, null, t);
            return null;
        }

        throw new RequeteException("erreur", "Demande inexistante.");
    }

}
