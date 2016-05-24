package fr.insalyon.ihm.controleur.gestionnaires;

import fr.insalyon.ihm.controleur.exceptions.RequeteException;
import java.util.Date;
import java.util.HashMap;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.http.HttpServletRequest;
import metier.modele.Activite;
import metier.modele.Adherent;
import metier.service.ServiceMetier;

public class GestionEffectuerDemande implements GestionnaireRequete {

    protected HashMap<Integer, Activite> activites = null;

    public GestionEffectuerDemande(HashMap<Integer, Activite> activites) {
        this.activites = activites;
    }

    @Override
    public Object traiterRequete(HttpServletRequest requete)
            throws RequeteException {
        String date = requete.getParameter("date");
        int noActivite = Integer.parseInt(requete.getParameter("activite"));

        try {
            Activite activite = activites.get(noActivite);
            if (activite != null) {
                Adherent adherent = (Adherent) requete.getSession().getAttribute("adherent");
                ServiceMetier.creerDemande(new Date(Long.parseLong(date)), adherent, activite);
            } else
                throw new Throwable();
        } catch (Throwable t) {
            throw new RequeteException("erreur", "Demande impossible.");
        }
        return true;
    }

}
