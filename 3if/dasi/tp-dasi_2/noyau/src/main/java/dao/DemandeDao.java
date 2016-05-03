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
import com.google.maps.model.LatLng;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import metier.modele.Demande;
import util.GeoTest;

public class DemandeDao {
    
    public static boolean create(Demande demande) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(demande);
            return true;
        }
        catch(Exception e) {
            throw e;
        }
    }
    
    public static Demande update(Demande demande) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            demande = em.merge(demande);
        }
        catch(Exception e){
            throw e;
        }
        return demande;
    }
    
    public static Demande findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Demande demande = null;
        try {
            demande = em.find(Demande.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return demande;
    }
    
    public static List<Demande> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Demande> demandes = null;
        try {
            Query q = em.createQuery("SELECT l FROM Demande l");
            demandes = (List<Demande>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        return demandes;
    }
    
    public static List<Demande> trouverDemandesProches(Demande demande, int rayonKM) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        LinkedList<Demande> demandesOK = new LinkedList<Demande>();
        demandesOK.add(demande);
        List<Demande> demandes = trouverDemandesParDate(demande.getDate());
        LatLng demandeLL = GeoTest.getLatLng(demande.getAdherent().getAdresse());
        for(Demande d : demandes)
        {
            LatLng dLL = GeoTest.getLatLng(d.getAdherent().getAdresse());
            if(GeoTest.getFlightDistanceInKm(demandeLL, dLL)<rayonKM/2)
            {
                demandesOK.add(d);
            }
            for(Demande d2 : demandes)
            {
                LatLng d2LL = GeoTest.getLatLng(d2.getAdherent().getAdresse());
                if(GeoTest.getFlightDistanceInKm(dLL, d2LL)<rayonKM/2)
                {
                    demandesOK.add(d);
                } 
            }
        }
        return demandes;
    }
    
    public static List<Demande> trouverParAdherent(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Demande> demandes = null;
        try {
            Query q = em.createQuery("SELECT d FROM Demande d WHERE d.adherent.id=:id");
            q.setParameter("id", id);
            demandes = (List<Demande>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return demandes;
    }

    public static List<Demande> trouverDemandesParDate(Date date) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Demande> demandes = null;
        try {
            Query q = em.createQuery("SELECT l FROM Demande l WHERE l.date=:date");
            q.setParameter("date", date);
            demandes = (List<Demande>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return demandes;
    }
}
