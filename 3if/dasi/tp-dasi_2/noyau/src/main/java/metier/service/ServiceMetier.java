/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package metier.service;

import dao.ActiviteDao;
import dao.AdherentDao;
import dao.DemandeDao;
import dao.EvenementDao;
import dao.JpaUtil;
import dao.LieuDao;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import metier.modele.Activite;
import metier.modele.Adherent;
import metier.modele.Demande;
import metier.modele.Evenement;
import metier.modele.EvenementAvecEquipe;
import metier.modele.EvenementSansEquipe;
import metier.modele.Lieu;

/**
 *
 * @author ovicente
 */
public class ServiceMetier {
    
    static final int RAYON_KM = 10;  
    
    public static Adherent inscrireAdherent(String nom, String prenom, String adresse, String mail) throws Throwable
    {
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();
        Adherent adherent = new Adherent(nom,prenom,adresse,mail);
        AdherentDao.create(adherent);
        JpaUtil.validerTransaction();
        JpaUtil.fermerEntityManager();
        return adherent;
    }
    
    public static Adherent connecterAdherent(String mail) throws Throwable
    {
        JpaUtil.creerEntityManager();
        Adherent adherent = AdherentDao.findByMail(mail);
        JpaUtil.fermerEntityManager();
        return adherent;
    }
    
    public static List<Demande> listerDemandes(Adherent adherent) throws Throwable
    {
        JpaUtil.creerEntityManager();
        List<Demande> demandes = DemandeDao.trouverParAdherent(adherent.getId());
        JpaUtil.fermerEntityManager();
        return demandes;
    }
    
    public static boolean creerDemande(Date date, Adherent adherent, Activite activite) throws Throwable
    {
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();
        Demande demande = new Demande(date, adherent, activite);
        boolean result = false;
        if(DemandeDao.create(demande))
        {
            result = true;
            List<Demande> demandes = DemandeDao.trouverDemandesProches(demande, RAYON_KM);
            if(demandes.size()>=demande.getActivite().getNbParticipants())
            {
                if(demande.getActivite().isParEquipe())
                {
                    EvenementAvecEquipe evenement = new EvenementAvecEquipe(demande.getDate(),demande.getActivite(),demandes);
                    EvenementDao.create(evenement);
                }
                else
                {
                    EvenementSansEquipe evenement = new EvenementSansEquipe(demande.getDate(),demande.getActivite(),demandes);
                    EvenementDao.create(evenement);
                }
            }
        }
        JpaUtil.validerTransaction();
        JpaUtil.fermerEntityManager();
        return result;
    }
    
    public static List<Evenement> listerEvenements(Adherent adherent) throws Throwable 
    {
        JpaUtil.creerEntityManager();
        List<Evenement> evenements = EvenementDao.trouverParAdherent(adherent.getId());
        JpaUtil.fermerEntityManager();
        return evenements;
    }

    public static List<Activite> listerActivites() throws Throwable
    {
        JpaUtil.creerEntityManager();
        List<Activite> activites = ActiviteDao.trouverToutes();
        JpaUtil.fermerEntityManager();
        return activites;
    }
    
    public static Evenement affecterLieu(Evenement evenement, Lieu lieu) throws Throwable
    {
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();
        evenement.setLieu(lieu);
        Evenement result = EvenementDao.update(evenement);
        JpaUtil.validerTransaction();
        JpaUtil.fermerEntityManager();
        return result;
    }
    
    public static List<Evenement> listerEvenements() throws Throwable
    {
        JpaUtil.creerEntityManager();
        List<Evenement> evenements = EvenementDao.trouverTout();
        JpaUtil.fermerEntityManager();
        return evenements;
    }
    
    public static List<Evenement> listerEvenementsSansLieu() throws Throwable
    {
        JpaUtil.creerEntityManager();
        List<Evenement> evenements = EvenementDao.trouverSansLieu();
        JpaUtil.fermerEntityManager();
        return evenements;
    }
    
    public static List<Lieu> listerLieux() throws Throwable
    {
        JpaUtil.creerEntityManager();
        List<Lieu> lieux = LieuDao.trouverTout();
        JpaUtil.fermerEntityManager();
        return lieux;
    }
    
    public static List<Adherent> listerParticipants(Evenement evenement) throws Throwable
    {
        JpaUtil.creerEntityManager();
        //List<Adherent> participants = EvenementDao.listerParticipants();
        List<Demande> demandes = evenement.getDemandes();
        List<Adherent> participants = new LinkedList<>();
        for(Demande d : demandes)
        {
            participants.add(d.getAdherent());
        }
        JpaUtil.fermerEntityManager();
        return participants;
    }
    
    public static boolean creerActivite(String denomination, boolean parEquipe, Integer nbParticipants) throws Throwable
    {
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();
        Activite activite = new Activite(denomination,parEquipe,nbParticipants);
        boolean result = ActiviteDao.create(activite);
        JpaUtil.validerTransaction();
        JpaUtil.fermerEntityManager();
        return result;
    }
    
    public static boolean creerLieu(String denomination, String description, String adresse) throws Throwable
    {
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();
        Lieu lieu = new Lieu(denomination,description,adresse);
        boolean result = LieuDao.create(lieu);
        JpaUtil.validerTransaction();
        JpaUtil.fermerEntityManager();
        return result;
    }
}
