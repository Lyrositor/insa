package fr.insalyon.ihm.controleur.gestionnaires;

import fr.insalyon.ihm.controleur.exceptions.RequeteException;
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
            throw new RequeteException("erreur", "E-mail inexistante");
        }

        // Vérifier si l'adhérent existe
        if (adherent == null)
            throw new RequeteException("erreur", "E-mail inexistante");
        requete.getSession().setAttribute("adherent", adherent);
        return adherent;
    }

}
