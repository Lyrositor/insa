package fr.insalyon.ihm.controleur.gestionnaires;

import fr.insalyon.ihm.controleur.exceptions.RequeteException;
import java.util.HashMap;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.http.HttpServletRequest;
import metier.modele.Evenement;
import metier.modele.Lieu;
import metier.service.ServiceMetier;

public class GestionAffecterLieu implements GestionnaireRequete {

    protected HashMap<Integer, Lieu> lieux = null;

    public GestionAffecterLieu(HashMap<Integer, Lieu> lieux) {
        this.lieux = lieux;
    }

    @Override
    public Object traiterRequete(HttpServletRequest requete)
            throws RequeteException {
        Integer evenementId = Integer.parseInt(requete.getParameter("evenement"));
        Integer lieuId = Integer.parseInt(requete.getParameter("lieu"));

        Evenement evenement = null;
        Lieu lieu = lieux.get(lieuId);
        try {
            for (Evenement e : ServiceMetier.listerEvenements())
                if (e.getId().equals(evenementId)) {
                    evenement = e;
                    break;
                }

            if (lieu == null || evenement == null)
                return false;
            ServiceMetier.affecterLieu(evenement, lieu);
        } catch (Throwable t) {
            return false;
        }

        return true;
    }

}
