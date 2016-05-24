package fr.insalyon.ihm.controleur.gestionnaires;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.http.HttpServletRequest;
import metier.service.ServiceMetier;

public class GestionListerEvenementsSansLieu implements GestionnaireRequete {

    @Override
    public Object traiterRequete(HttpServletRequest requete) {
        try {
            return ServiceMetier.listerEvenementsSansLieu();
        } catch (Throwable ex) {
            Logger.getLogger(getClass().getName()).log(Level.SEVERE, null, ex);
        }
        return null;
    }

}
