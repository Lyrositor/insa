package fr.insalyon.gustatif.dao;

import fr.insalyon.gustatif.metier.modele.Livraison;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;

public class LivraisonDao {

    public void create(Livraison livraison) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(livraison);
        } catch (Exception e) {
            throw e;
        }
    }

    public Livraison update(Livraison livraison) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            livraison = em.merge(livraison);
        } catch (Exception e) {
            throw e;
        }
        return livraison;
    }

    public Livraison findById(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Livraison livraison = null;
        try {
            livraison = em.find(Livraison.class, id);
        } catch (Exception e) {
            throw e;
        }
        return livraison;
    }

    public List<Livraison> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Livraison> livraisons = null;
        try {
            Query q = em.createQuery("SELECT l FROM Livraison l ORDER BY l.nom");
            livraisons = (List<Livraison>) q.getResultList();
        } catch (Exception e) {
            throw e;
        }
        return livraisons;
    }
}
