package fr.insalyon.gustatif.dao;

import fr.insalyon.gustatif.metier.modele.Gestionnaire;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;

public class GestionnaireDao {

    public void create(Gestionnaire gestionnaire) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(gestionnaire);
        } catch (Exception e) {
            throw e;
        }
    }

    public Gestionnaire update(Gestionnaire gestionnaire) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            gestionnaire = em.merge(gestionnaire);
        } catch (Exception e) {
            throw e;
        }
        return gestionnaire;
    }

    public Gestionnaire findById(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Gestionnaire gestionnaire = null;
        try {
            gestionnaire = em.find(Gestionnaire.class, id);
        } catch (Exception e) {
            throw e;
        }
        return gestionnaire;
    }

    public Gestionnaire findByMail(String mail) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Gestionnaire gestionnaire = null;
        try {
            Query q = em.createQuery("SELECT g FROM Gestionnaire g WHERE mail=:mail");
            q.setParameter("mail", mail);
            gestionnaire = (Gestionnaire) q.getSingleResult();
        } catch (Exception e) {
            throw e;
        }
        return gestionnaire;
    }

    public List<Gestionnaire> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Gestionnaire> gestionnaires = null;
        try {
            Query q = em.createQuery("SELECT g FROM Gestionnaire g ORDER BY g.nom");
            gestionnaires = (List<Gestionnaire>) q.getResultList();
        } catch (Exception e) {
            throw e;
        }
        return gestionnaires;
    }
}
