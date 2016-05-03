/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dao;

/**
 *
 * @author ovicente
 */
import java.util.LinkedList;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import metier.modele.Demande;
import metier.modele.Evenement;

public class EvenementDao {
    
    public static void create(Evenement evenement) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(evenement);
        }
        catch(Exception e) {
            throw e;
        }
    }
    
    public static Evenement update(Evenement evenement) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            evenement = em.merge(evenement);
        }
        catch(Exception e){
            throw e;
        }
        return evenement;
    }
    
    public static Evenement findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Evenement evenement = null;
        try {
            evenement = em.find(Evenement.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return evenement;
    }
    
    public static List<Evenement> trouverTout() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Evenement> evenements = null;
        try {
            Query q = em.createQuery("SELECT e FROM Evenement e");
            evenements = (List<Evenement>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        return evenements;
    }
    
    public static List<Evenement> trouverParAdherent(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Demande> demandes = null;
        List<Evenement> evenements = new LinkedList<>();
        try {
            Query q = em.createQuery("SELECT d FROM Demande d WHERE d.adherent.id=:id "
                    + "and d.evenement is not null");
            q.setParameter("id", id);
            demandes = (List<Demande>) q.getResultList();    
            for(Demande d : demandes)
            {
                evenements.add(d.getEvenement());
            }
        }
        catch(Exception e) {
            throw e;
        }
        return evenements;
    }
    
    public static List<Evenement> trouverSansLieu() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Evenement> evenements = null;
        try {
            Query q = em.createQuery("SELECT e FROM Evenement e WHERE e.lieu is null");
            evenements = (List<Evenement>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        return evenements;
    }
    
    /*public static List<Adherent> listerParticipants() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Adherent> participants = null;
        try {
            Query q = em.createQuery("SELECT e FROM Evenement WHERE lieu = :lieu");
            q.setParameter("lieu", null);
            participants = (List<Adherent>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        return participants;
    }*/
}
