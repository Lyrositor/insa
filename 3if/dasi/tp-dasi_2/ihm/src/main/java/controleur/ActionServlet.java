package controleur;

import com.google.gson.Gson;
import com.google.gson.JsonObject;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import metier.modele.Activite;
import metier.modele.Adherent;
import metier.service.ServiceMetier;

@WebServlet(name = "ActionServlet", urlPatterns = {"/ActionServlet"})
public class ActionServlet extends HttpServlet {

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        System.out.println("Un appel !" + request.toString());

        if (request.getParameter("action") == null) {
            response.sendRedirect(getServletContext().getContextPath());
            return;
        }

        Gson gson = new Gson();

        switch (request.getParameter("action")) {
            case "listeActivite":
                response.setContentType("application/json;charset=UTF-8");
                try (PrintWriter out = response.getWriter()) {
                    String json = gson.toJson(listerActivites());

                    out.println(json);
                }
                break;
            case "authentification":
                response.setContentType("application/json;charset=UTF-8");
                try (PrintWriter out = response.getWriter()) {
                    String json;

                    String email = request.getParameter("email");
                    Adherent adherent = connecterAdherent(email);
                    // Si l'adhérent n'a pas été trouvé
                    if (adherent == null) {
                        JsonObject jsonObject = new JsonObject();
                        jsonObject.addProperty("erreur", "Email inexistante.");
                        json = jsonObject.toString();
                    } else {
                        json = gson.toJson(adherent);
                    }

                    out.println(json);
                }
                break;
            default:
                response.sendRedirect(getServletContext().getContextPath());
                break;
        }
    }

    private static List<Activite> listerActivites() {
        List<Activite> activites = null;
        try {
            activites = ServiceMetier.listerActivites();
        } catch (Throwable ex) {
            Logger.getLogger(ActionServlet.class.getName()).log(Level.SEVERE, null, ex);
        }
        System.out.println("IHM - Activite :");
        System.out.println(activites);
        return activites;
    }

    private static Adherent connecterAdherent(String email) {
        System.out.println("connecterAdherent: " + email);

        Adherent adherent = null;
        try {
            adherent = ServiceMetier.connecterAdherent(email);
        } catch (Throwable ex) {
            Logger.getLogger(ActionServlet.class.getName()).log(Level.SEVERE, null, ex);
        }

        return adherent;
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
