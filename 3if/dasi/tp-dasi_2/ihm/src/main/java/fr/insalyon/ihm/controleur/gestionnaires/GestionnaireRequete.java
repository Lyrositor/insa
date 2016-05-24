package fr.insalyon.ihm.controleur.gestionnaires;

import fr.insalyon.ihm.controleur.exceptions.RequeteException;
import javax.servlet.http.HttpServletRequest;

public interface GestionnaireRequete {

    public Object traiterRequete(HttpServletRequest requete)
            throws RequeteException;

}
