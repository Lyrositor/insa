package fr.insalyon.gustatif.dao;

import fr.insalyon.gustatif.metier.modele.Cycliste;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;

public class CyclisteDao {

    public void create(Cycliste cycliste) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(cycliste);
        } catch (Exception e) {
            throw e;
        }
    }

    public Cycliste update(Cycliste cycliste) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            cycliste = em.merge(cycliste);
        } catch (Exception e) {
            throw e;
        }
        return cycliste;
    }

    public Cycliste findById(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Cycliste cycliste = null;
        try {
            cycliste = em.find(Cycliste.class, id);
        } catch (Exception e) {
            throw e;
        }
        return cycliste;
    }

    public List<Cycliste> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Cycliste> cyclistes = null;
        try {
            Query q = em.createQuery("SELECT c FROM Cycliste c ORDER BY c.nom");
            cyclistes = (List<Cycliste>) q.getResultList();
        } catch (Exception e) {
            throw e;
        }
        return cyclistes;
    }
}
