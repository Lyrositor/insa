package fr.insalyon.gustatif.metier.modele;

/**
 *
 * @author afavier
 */
public class Gestionnaire {

    private String email;
    private String motDePasse;

    public Gestionnaire() {
    }

    public Gestionnaire(String email, String motDePasse) {
        this.email = email;
        this.motDePasse = motDePasse;
    }

    public String getEmail() {
        return email;
    }

    public String getMotDePasse() {
        return motDePasse;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setMotDePasse(String motDePasse) {
        this.motDePasse = motDePasse;
    }

}
