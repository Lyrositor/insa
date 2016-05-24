package fr.insalyon.ihm.controleur.gestionnaires;

import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;
import metier.modele.Activite;

public class GestionListerActivites implements GestionnaireRequete {

    protected HashMap<Integer, Activite> activites = null;

    public GestionListerActivites(HashMap<Integer, Activite> activites) {
        this.activites = activites;
    }

    @Override
    public Object traiterRequete(HttpServletRequest requete) {
        return activites.values();
    }

}
