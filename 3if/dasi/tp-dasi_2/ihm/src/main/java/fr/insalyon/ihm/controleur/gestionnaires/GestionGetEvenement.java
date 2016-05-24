package fr.insalyon.ihm.controleur.gestionnaires;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.http.HttpServletRequest;
import metier.modele.Evenement;
import metier.service.ServiceMetier;

public class GestionGetEvenement implements GestionnaireRequete {

    @Override
    public Object traiterRequete(HttpServletRequest requete) {
        Integer id = Integer.parseInt(requete.getParameter("id"));

        try {
            for (Evenement e : ServiceMetier.listerEvenements())
                if (e.getId().equals(id))
                    return e;
        } catch (Throwable ex) {
            Logger.getLogger(getClass().getName()).log(Level.SEVERE, null, ex);
        }
        return null;
    }

}
