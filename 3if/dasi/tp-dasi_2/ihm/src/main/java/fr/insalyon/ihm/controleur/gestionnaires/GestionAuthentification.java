package fr.insalyon.ihm.controleur.gestionnaires;

import fr.insalyon.ihm.controleur.exceptions.RequeteException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.http.HttpServletRequest;
import metier.modele.Adherent;
import metier.service.ServiceMetier;

public class GestionAuthentification implements GestionnaireRequete {

    @Override
    public Object traiterRequete(HttpServletRequest requete)
            throws RequeteException {
        String email = requete.getParameter("email");

        Adherent adherent = null;
        try {
            adherent = ServiceMetier.connecterAdherent(email);
        } catch (Throwable t) {
            Logger.getLogger(getClass().getName()).log(Level.SEVERE, null, t);
            return null;
        }

        // Vérifier si l'adhérent existe
        String json;
        if (adherent == null)
            throw new RequeteException("erreur", "E-mail inexistante");
        requete.getSession().setAttribute("adherent", adherent);
        return adherent;
    }

}
