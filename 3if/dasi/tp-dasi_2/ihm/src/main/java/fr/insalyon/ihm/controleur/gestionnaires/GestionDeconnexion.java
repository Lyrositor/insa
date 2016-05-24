package fr.insalyon.ihm.controleur.gestionnaires;

import fr.insalyon.ihm.controleur.exceptions.RequeteException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

public class GestionDeconnexion implements GestionnaireRequete {

    @Override
    public Object traiterRequete(HttpServletRequest requete)
            throws RequeteException {
        HttpSession session = requete.getSession();
        if (session.getAttribute("adherent") != null) {
            session.removeAttribute("adherent");
            return true;
        }
        return false;
    }

}
