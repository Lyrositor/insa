package fr.insalyon.ihm.controleur.gestionnaires;

import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;
import metier.modele.Lieu;


public class GestionListerLieux implements GestionnaireRequete {

    protected HashMap<Integer, Lieu> lieux = null;

    public GestionListerLieux(HashMap<Integer, Lieu> lieux) {
        this.lieux = lieux;
    }

    @Override
    public Object traiterRequete(HttpServletRequest requete) {
        return lieux.values();
    }

}
