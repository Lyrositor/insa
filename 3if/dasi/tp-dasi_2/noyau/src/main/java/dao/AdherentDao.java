package dao;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import metier.modele.Adherent;

public class AdherentDao {
    
    public static boolean create(Adherent adherent) throws Throwable {
        if(adherent.getLatitude()!=null)
        {
            EntityManager em = JpaUtil.obtenirEntityManager();
            try {
                em.persist(adherent);
                return true;
            }
            catch(Exception e) {
                throw e;
            }
        }
        return false;
    }
    
    public static Adherent update(Adherent adherent) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            adherent = em.merge(adherent);
        }
        catch(Exception e){
            throw e;
        }
        return adherent;
    }
    
    public static Adherent findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Adherent adherent = null;
        try {
            adherent = em.find(Adherent.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return adherent;
    }
    
    public static Adherent findByMail(String mail) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Adherent adherent = null;
        try {
            Query q = em.createQuery("SELECT a FROM Adherent a WHERE a.mail=:mail");
            q.setParameter("mail", mail);
            adherent = (Adherent) q.getSingleResult();
        }
        catch(Exception e) {
            throw e;
        }
        return adherent;
    }
    
    public static List<Adherent> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Adherent> adherents = null;
        try {
            Query q = em.createQuery("SELECT a FROM Adherent a");
            adherents = (List<Adherent>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        return adherents;
    }
}
