package fr.insalyon.gustatif.dao;

import fr.insalyon.gustatif.metier.modele.Cycliste;
import javax.persistence.EntityManager;
import javax.persistence.Query;

public class CyclisteDao {

    public Cycliste findByMail(String mail) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Cycliste cycliste = null;
        try {
            Query q = em.createQuery("SELECT c FROM Cycliste c WHERE c.mail=:mail");
            q.setParameter("mail", mail);
            cycliste = (Cycliste) q.getSingleResult();
        } catch (Exception e) {
            throw e;
        }
        return cycliste;
    }

}
