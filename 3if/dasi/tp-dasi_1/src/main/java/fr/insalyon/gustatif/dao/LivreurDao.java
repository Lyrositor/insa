package fr.insalyon.gustatif.dao;

import fr.insalyon.gustatif.metier.modele.Livreur;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;

public class LivreurDao {

    public void create(Livreur livreur) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(livreur);
        } catch (Exception e) {
            throw e;
        }
    }

    public Livreur update(Livreur livreur) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            livreur = em.merge(livreur);
        } catch (Exception e) {
            throw e;
        }
        return livreur;
    }

    public Livreur findById(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Livreur livreur = null;
        try {
            livreur = em.find(Livreur.class, id);
        } catch (Exception e) {
            throw e;
        }
        return livreur;
    }

    public List<Livreur> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Livreur> livreurs = null;
        try {
            Query q = em.createQuery("SELECT l FROM Livreur l ORDER BY l.nom");
            livreurs = (List<Livreur>) q.getResultList();
        } catch (Exception e) {
            throw e;
        }
        return livreurs;
    }

    public List<Livreur> findAllAvalaibleWithCapacity(Float poids) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Livreur> livreurs = null;
        try {
            //Query q = em.createQuery("SELECT l FROM Livreur l WHERE disponible = true and capacity >= poids ORDER BY l.nom");
            Query q = em.createQuery("SELECT l FROM Livreur l ORDER BY l.nom");
            livreurs = (List<Livreur>) q.getResultList();
        } catch (Exception e) {
            throw e;
        }
        return livreurs;
    }
}
