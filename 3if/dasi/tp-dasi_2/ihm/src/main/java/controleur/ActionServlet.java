package controleur;

import com.google.gson.Gson;
import com.google.gson.JsonObject;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Date;
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
import metier.modele.Demande;
import metier.modele.Evenement;
import metier.modele.Lieu;
import metier.service.ServiceMetier;

@WebServlet(name = "ActionServlet", urlPatterns = {"/ActionServlet"})
public class ActionServlet extends HttpServlet {

    protected List<Activite> activites = null;
    protected List<Lieu> lieux = null;

    @Override
    public void init() {
        try {
            activites = ServiceMetier.listerActivites();
            lieux = ServiceMetier.listerLieux();
        } catch (Throwable ex) {
            Logger.getLogger(ActionServlet.class.getName()).log(Level.SEVERE, null, ex);
        }
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
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        System.out.println(request.toString());

        if (request.getParameter("action") == null) {
            response.sendRedirect(getServletContext().getContextPath());
            return;
        }

        Gson gson = new Gson();

        PrintWriter out = response.getWriter();
        response.setContentType("application/json;charset=UTF-8");

        switch (request.getParameter("action")) {
            case "listeActivites": {
                out.print(gson.toJson(activites));
                break;
            }

            case "authentification": {
                String email = request.getParameter("email");
                Adherent adherent = connecterAdherent(email);
                // Si l'adhérent n'a pas été trouvé
                String json;
                if (adherent == null) {
                    JsonObject jsonObject = new JsonObject();
                    jsonObject.addProperty("erreur", "E-mail inexistante.");
                    json = jsonObject.toString();
                } else {
                    json = gson.toJson(adherent);

                    request.getSession().setAttribute("adherent", adherent);
                }

                out.print(json);
                break;
            }

            case "inscription": {
                String nom = request.getParameter("nom");
                String prenom = request.getParameter("prenom");
                String adresse = request.getParameter("adresse");
                String email = request.getParameter("email");

                Adherent adherent = inscrireAdherent(nom, prenom, adresse, email);
                // Si l'adhérent n'a pas été inscrit
                String json;
                if (adherent == null) {
                    JsonObject jsonObject = new JsonObject();
                    jsonObject.addProperty("erreur", "Inscription impossible.");
                    json = jsonObject.toString();
                } else {
                    json = gson.toJson(adherent);
                }

                out.print(json);
                break;
            }

            case "listerEvenementsSansLieu": {
                out.print(gson.toJson(listerEvenementsSansLieu()));
                break;
            }

            case "listerLieux": {
                out.print(gson.toJson(lieux));
                break;
            }

            case "getEvenement": {
                Integer id = Integer.parseInt(request.getParameter("id"));
                out.print(gson.toJson(getEvenement(id)));
                break;
            }

            case "affecterLieu": {
                Integer evenementId = Integer.parseInt(request.getParameter("evenement"));
                Integer lieuId = Integer.parseInt(request.getParameter("lieu"));
                affecterLieu(evenementId, lieuId);
                break;
            }

            case "listeDemandes": {
                Adherent adherent = (Adherent) request.getSession().getAttribute("adherent");

                try {
                    List<Demande> demandes = ListerDemandes(adherent);
                    out.print(gson.toJson(demandes));

                    break;
                } catch (Throwable ex) {
                    Logger.getLogger(ActionServlet.class.getName()).log(Level.SEVERE, null, ex);
                }

                JsonObject jsonObject = new JsonObject();
                jsonObject.addProperty("erreur", "Liste des demandes impossible.");
                out.print(jsonObject.toString());
                break;
            }

            case "effectuerDemande": {
                String date = request.getParameter("date");
                int noActivite = Integer.parseInt(request.getParameter("activite"));

                Boolean error = true;
                try {
                    Activite activiteSelectionnee = null;
                    for (Activite activite : ServiceMetier.listerActivites()) {
                        if (activite.getId() == noActivite) {
                            activiteSelectionnee = activite;
                            break;
                        }
                    }
                    if (activiteSelectionnee != null) {
                        Adherent adherent = (Adherent) request.getSession().getAttribute("adherent");

                        error = !effectuerDemande(new Date(Long.parseLong(date)), adherent, activiteSelectionnee);
                    }
                } catch (Throwable ex) {
                    Logger.getLogger(ActionServlet.class.getName()).log(Level.SEVERE, null, ex);
                    error = true;
                }

                JsonObject jsonObject = new JsonObject();
                String json;
                if (error) {
                    jsonObject.addProperty("erreur", "Demande impossible.");
                    json = jsonObject.toString();
                } else {
                    jsonObject.addProperty("succes", "");
                    json = jsonObject.toString();
                }

                out.print(json);
                break;
            }

            case "getDemande": {
                int demandeId = Integer.parseInt(request.getParameter("demande"));
                Adherent adherent = (Adherent) request.getSession().getAttribute("adherent");

                Boolean error = true;
                for (Demande demande : ListerDemandes(adherent)) {
                    if (demande.getId() == demandeId) {
                        out.print(gson.toJson(demande));
                        error = false;
                        break;
                    }
                }

                if (error == true) {
                    JsonObject jsonObject = new JsonObject();
                    jsonObject.addProperty("erreur", "Demande inexistante.");
                    out.print(jsonObject.toString());
                }

                break;
            }

            case "deconnexion": {
                request.getSession().removeAttribute("adherent");
                break;
            }

            default:
                response.sendRedirect(getServletContext().getContextPath());
                break;
        }
    }

    private Adherent connecterAdherent(String email) {
        Adherent adherent = null;
        try {
            adherent = ServiceMetier.connecterAdherent(email);
        } catch (Throwable ex) {
            Logger.getLogger(ActionServlet.class.getName()).log(Level.SEVERE, null, ex);
        }
        return adherent;
    }

    private Adherent inscrireAdherent(String nom, String prenom, String adresse, String mail) {
        Adherent adherent = null;
        try {
            adherent = ServiceMetier.inscrireAdherent(nom, prenom, adresse, mail);
        } catch (Throwable ex) {
            Logger.getLogger(ActionServlet.class.getName()).log(Level.SEVERE, null, ex);
        }
        return adherent;
    }

    private Evenement getEvenement(Integer id) {
        try {
            for (Evenement e : ServiceMetier.listerEvenements()) {
                if (e.getId().equals(id)) {
                    return e;
                }
            }
        } catch (Throwable ex) {
            Logger.getLogger(ActionServlet.class.getName()).log(Level.SEVERE, null, ex);
        }
        return null;
    }

    private List<Evenement> listerEvenementsSansLieu() {
        List<Evenement> evenements = null;
        try {
            evenements = ServiceMetier.listerEvenementsSansLieu();
        } catch (Throwable ex) {
            Logger.getLogger(ActionServlet.class.getName()).log(Level.SEVERE, null, ex);
        }
        return evenements;
    }

    private void affecterLieu(Integer evenementId, Integer lieuId) {
        Evenement evenement = null;
        Lieu lieu = null;
        try {
            for (Evenement e : ServiceMetier.listerEvenements()) {
                if (e.getId().equals(evenementId)) {
                    evenement = e;
                    break;
                }
            }
            for (Lieu l : lieux) {
                if (l.getId().equals(lieuId)) {
                    lieu = l;
                    break;
                }
            }
            if (lieu == null || evenement == null) {
                return;
            }
            ServiceMetier.affecterLieu(evenement, lieu);
        } catch (Throwable ex) {
            Logger.getLogger(ActionServlet.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private boolean effectuerDemande(Date date, Adherent adherent, Activite activite) {
        try {
            ServiceMetier.creerDemande(date, adherent, activite);
            return true;
        } catch (Throwable ex) {
            Logger.getLogger(ActionServlet.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        }
    }

    private List<Demande> ListerDemandes(Adherent adherent) {
        try {
            return ServiceMetier.listerDemandes(adherent);
        } catch (Throwable ex) {
            Logger.getLogger(ActionServlet.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
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
