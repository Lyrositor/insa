/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package vue;

import java.util.Date;
import java.util.List;
import metier.modele.Activite;
import metier.modele.Adherent;
import metier.modele.Demande;
import metier.modele.Evenement;
import metier.modele.Lieu;
import metier.service.ServiceMetier;
import util.Saisie;

/**
 *
 * @author ovicente
 */
public class Main {
    
    public static void main(String[] args) throws Throwable {
        System.out.println("Bonjour. Que voulez-vous faire ?");
        lancerMenu();
    }
    
 ///////////////////////////////////////////////////////////////////////////////
    // Menu Principal
    public static void lancerMenu() throws Throwable
    {
        int input = 0;
        while(input != 9) {
            input = Saisie.lireInteger("1-Se connecter / 2-S'inscrire /"
                    + " 3-Menu Responsable / 4-Menu de Gestion / 9-Exit\n");
            switch(input) {
                case 1:
                    Adherent adherent = connexion();
                    lancerMenu2(adherent);
                    break;
                case 2:
                    Adherent newAdherent = inscription();
                    lancerMenu2(newAdherent);
                    break;
                case 3:
                    lancerMenuResponsable();
                    break;
                case 4:
                    lancerMenuGestion();
                    break;
                case 9:
                    break;
                default:
                    System.out.println("Commande non connue réessayez");
            }
        }
    }
    
    public static Adherent connexion() throws Throwable
    {
        String mail = Saisie.lireChaine("Entrez votre adresse email :");
        return ServiceMetier.connecterAdherent(mail);
    }
    
    public static Adherent inscription() throws Throwable
    {
        String nom = Saisie.lireChaine("Entrez votre nom :");
        String prenom = Saisie.lireChaine("Entrez votre prenom :");
        String adresse = Saisie.lireChaine("Entrez votre adresse :");
        String mail = Saisie.lireChaine("Entrez votre mail :");
        return ServiceMetier.inscrireAdherent(nom, prenom, adresse, mail);
    }

 ///////////////////////////////////////////////////////////////////////////////
    // Menu Utilisateur
    public static void lancerMenu2(Adherent adherent) throws Throwable
    {
        int input = 0;
        while(input != 9) {
            input = Saisie.lireInteger("1-Effectuer une demande d'événement /"
                    + " 2-Lister les demandes en cours /"
                    + " 3-Lister les événements planifiés/ 9-Exit \n");
            switch(input) {
                case 1:
                    effectuerDemande(adherent);
                    break;
                case 2:
                    listerDemandes(adherent);
                    break;
                case 3:
                    listerEvenements(adherent);
                    break;
                case 9:
                    break;
                default:
                    System.out.println("Commande non connue réessayez");
            }
        }
    }
    
    public static void effectuerDemande(Adherent adherent) throws Throwable
    {
        int day = Saisie.lireInteger("Entrez le jour de l'évenement en chiffre :");
        int month = Saisie.lireInteger("Entrez le mois de l'évenement en chiffre :");
        int year = Saisie.lireInteger("Entrez l'année de l'évenement :");
        Date date = new Date(year, month, day);
        List<Activite> activites = ServiceMetier.listerActivites();
        System.out.println("Liste des activités :");
        for(Activite a : activites)
        {
            System.out.println("Activite "+activites.indexOf(a)+" : "+a.getDenomination());
        }
        int noActivite = Saisie.lireInteger("Entrez le numero de l'activite :");
        Activite activite = activites.get(noActivite);
        ServiceMetier.creerDemande(date, adherent, activite);
    }
    
    public static void listerDemandes(Adherent adherent) throws Throwable
    {
        List<Demande> demandes = ServiceMetier.listerDemandes(adherent);
        System.out.println("Liste de vos demandes :");
        for(Demande d : demandes)
        {
            System.out.println("- "+d);
        }
    }
    
    public static void listerEvenements(Adherent adherent) throws Throwable
    {
        List<Evenement> evenements = ServiceMetier.listerEvenements(adherent);
        System.out.println("Liste de vos événements :");
        for(Evenement e : evenements)
        {
            System.out.println("- "+e);
        }
    }

 ///////////////////////////////////////////////////////////////////////////////   
    //Menu du Responsable
    public static void lancerMenuResponsable() throws Throwable
    {
        int input = 0;
        while(input != 9) {
            input = Saisie.lireInteger("1-Affecter lieu à un événement non "
                    + "planifiées / 2-Lister tous les événements / 3-Lister les "
                    + "lieux / 9-Exit");
            switch(input) {
                case 1:
                    affecterLieuEvenement();
                    break;
                case 2:
                    listerEvenements();
                    break;
                case 3:
                    listerLieux();
                    break;
                case 9:
                    break;
                default:
                    System.out.println("Commande non connue réessayez");
            }
        }
    }
    
    public static void affecterLieuEvenement() throws Throwable
    {
        //choix événement à modifier
        List<Evenement> evenements = ServiceMetier.listerEvenementsSansLieu();
        System.out.println("Liste des événements :");
        for(Evenement e : evenements)
        {
            System.out.println("Evénement "+evenements.indexOf(e)+" : "+e);
        }
        int noEvenement = Saisie.lireInteger("Entrez le numero de l'événement "
                + "dont le lieu sera affecté : ");
        Evenement evenement = evenements.get(noEvenement);
        //liste des participants
        List<Adherent> participants = ServiceMetier.listerParticipants(evenement);
        System.out.println("Liste des participants :");
        for(Adherent a : participants)
        {
            System.out.println("Participant "+participants.indexOf(a)+" : "+a);
        }
        //choix lieu à affecter
        List<Lieu> lieux = ServiceMetier.listerLieux();
        System.out.println("Liste des lieux :");
        for(Lieu l : lieux)
        {
            System.out.println("Lieu "+lieux.indexOf(l)+" : "+l);
        }
        int noLieu = Saisie.lireInteger("Entrez le numero du lieu à affecter :");
        Lieu l = lieux.get(noLieu);
        ServiceMetier.affecterLieu(evenement, l);
    }
    
    public static void listerEvenements() throws Throwable
    {
       List<Evenement> evenements = ServiceMetier.listerEvenements();
        System.out.println("Liste des lieux :");
        for(Evenement e : evenements)
        {
            System.out.println("- "+e);
        } 
    }
    
 ///////////////////////////////////////////////////////////////////////////////
    //Menu de Gestion
    public static void lancerMenuGestion() throws Throwable
    {
        int input = 0;
        while(input != 9) {
            input = Saisie.lireInteger("1-Gestion des Lieux / 2-Gestion des activités / 9-Exit\n");
            switch(input) {
                case 1:
                    gestionLieux();
                    break;
                case 2:
                    gestionActivites();
                    break;
                case 9:
                    break;
                default:
                    System.out.println("Commande non connue réessayez");
            }
        }
    }
    
    //Gestion des Lieux
    public static void gestionLieux() throws Throwable
    {
        int input = 0;
        while(input != 9) {
            input = Saisie.lireInteger(" 1-Ajouter un Lieu / 2-Lister les lieux / 9-Exit\n");
            switch(input) {
                case 1:
                    ajouterLieu();
                    break;
                case 2:
                    listerLieux();
                    break;
                case 9:
                    break;
                default:
                    System.out.println("Commande non connue réessayez");
            }
        }
    }
    
    public static void ajouterLieu() throws Throwable
    {
        String denomination = Saisie.lireChaine("Entrez la dénomination du lieu :");
        String description = Saisie.lireChaine("Entrez la description du lieu :");
        String adresse = Saisie.lireChaine("Entrez l'adresse du lieu :");
        ServiceMetier.creerLieu(denomination, description, adresse);
    }
    
    public static void listerLieux() throws Throwable
    {
        List<Lieu> lieux = ServiceMetier.listerLieux();
        System.out.println("Liste des lieux :");
        for(Lieu l : lieux)
        {
            System.out.println("- "+l);
        }
    }
    
    //Gestion des Activités
    public static void gestionActivites() throws Throwable
    {
        int input = 0;
        while(input != 9) {
            input = Saisie.lireInteger(" 1-Ajouter une Activité / 2-Lister les activités / 9-Exit\n");
            switch(input) {
                case 1:
                    ajouterActivite();
                    break;
                case 2:
                    listerActivites();
                    break;
                case 9:
                    break;
                default:
                    System.out.println("Commande non connue réessayez");
            }
        }
    }
    
    public static void ajouterActivite() throws Throwable
    {
        String denomination = Saisie.lireChaine("Entrez la dénomination de l'activité :");
        String equipe = Saisie.lireChaine("L'activité comporte-t-elle des équipes ?(O/N)");
        boolean parEquipe = false;
        if(equipe=="O")
        {
            parEquipe = true;
        }
        else if(equipe=="N")
        {
            parEquipe = false;
        }
        int nbParticipants = Saisie.lireInteger("Entrez le nombre de participants :");
        ServiceMetier.creerActivite(denomination, parEquipe, nbParticipants);
    }
    
    public static void listerActivites() throws Throwable
    {
        List<Activite> activites = ServiceMetier.listerActivites();
        System.out.println("Liste des activites :");
        for(Activite a : activites)
        {
            System.out.println("- "+a);
        }
    }
}
