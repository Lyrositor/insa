package dao;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import metier.modele.Lieu;

public class LieuDao {
    
    public static boolean create(Lieu lieu) throws Throwable {
        if(lieu.getLatitude()!=null){
            EntityManager em = JpaUtil.obtenirEntityManager();
            try {
                em.persist(lieu);
                return true;
            }
            catch(Exception e) {
                throw e;
            } 
        }
        return false;
    }
    
    public static Lieu update(Lieu lieu) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            lieu = em.merge(lieu);
        }
        catch(Exception e){
            throw e;
        }
        return lieu;
    }
    
    public static Lieu findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Lieu lieu = null;
        try {
            lieu = em.find(Lieu.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return lieu;
    }
    
    public static List<Lieu> trouverTout() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Lieu> lieux = null;
        try {
            Query q = em.createQuery("SELECT l FROM Lieu l");
            lieux = (List<Lieu>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return lieux;
    }
}
