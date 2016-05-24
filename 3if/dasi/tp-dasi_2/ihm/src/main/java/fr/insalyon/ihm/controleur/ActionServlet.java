package fr.insalyon.ihm.controleur;

import fr.insalyon.ihm.controleur.exceptions.RequeteException;
import fr.insalyon.ihm.controleur.gestionnaires.*;
import fr.insalyon.ihm.util.JsonConverter;
import java.io.IOException;
import java.util.HashMap;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import metier.modele.Activite;
import metier.modele.Lieu;
import metier.service.ServiceMetier;

@WebServlet(name = "ActionServlet", urlPatterns = {"/ActionServlet"})
public class ActionServlet extends HttpServlet {

    protected HashMap<String, GestionnaireRequete> gestionnaires = new HashMap();

    @Override
    public void init() {
        // Initialiser les données constantes
        HashMap<Integer, Activite> activites = new HashMap();
        HashMap<Integer, Lieu> lieux = new HashMap();
        try {
            for (Activite a : ServiceMetier.listerActivites())
                activites.put(a.getId(), a);
            for (Lieu l : ServiceMetier.listerLieux())
                lieux.put(l.getId(), l);
        } catch (Throwable ex) {
            Logger.getLogger(getClass().getName()).log(Level.SEVERE, null, ex);
            return;
        }

        // Initialiser les gestionnaires
        gerer("affecterLieu", new GestionAffecterLieu(lieux));
        gerer("authentification", new GestionAuthentification());
        gerer("deconnexion", new GestionDeconnexion());
        gerer("effectuerDemande", new GestionEffectuerDemande(activites));
        gerer("getDemande", new GestionGetDemande());
        gerer("getEvenement", new GestionGetEvenement());
        gerer("inscription", new GestionInscription());
        gerer("listeActivites", new GestionListerActivites(activites));
        gerer("listeDemandes", new GestionListerDemandes());
        gerer("listerEvenementsSansLieu", new GestionListerEvenementsSansLieu());
        gerer("listerLieux", new GestionListerLieux(lieux));
    }

    protected void gerer(String action, GestionnaireRequete gestionnaire) {
        gestionnaires.put(action, gestionnaire);
    }

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(
            HttpServletRequest request, HttpServletResponse response
    ) throws ServletException, IOException {

        System.out.println(request);

        String action;
        if ((action = request.getParameter("action")) == null) {
            response.sendRedirect(getServletContext().getContextPath());
            return;
        }

        // Vérifier qu'un gestionnaire pour cette requête existe
        GestionnaireRequete gestionnaire = gestionnaires.get(action);
        if (gestionnaire == null) {
            response.sendRedirect(getServletContext().getContextPath());
            return;
        }

        // Gérer la requête
        response.setContentType("application/json;charset=UTF-8");
        String json;
        try {
            json = JsonConverter.toJson(gestionnaire.traiterRequete(request));
        } catch (Throwable e) {
            System.out.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
            json = JsonConverter.toJsonMessage("succes", e.getMessage());
            System.out.println(json);
        }
        response.getWriter().print(json);
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
