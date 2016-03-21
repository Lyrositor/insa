package fr.insalyon.dasi.td.jpa;

import com.google.maps.model.LatLng;
import static fr.insalyon.dasi.td.jpa.Personne.getLatLng;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

public class Main {
    
    public static void main(String[] args) throws ParseException {
        
        EntityManagerFactory emf = Persistence.createEntityManagerFactory("conf");
        EntityManager em = emf.createEntityManager();
        SimpleDateFormat sdf = new SimpleDateFormat("dd MM yyyy");
        
        em.getTransaction().begin();
        
        Personne p1 = new Personne("Gripay", "Yan", sdf.parse("25 12 1978"), "7 avenue Jean Capelle, Villeurbanne");
        
        System.out.println("--- PERSIST: START ---");
        em.persist(p1);
        em.getTransaction().commit();
        System.out.println(p1);
        System.out.println("--- PERSIST: END ---");        
        
        System.out.println("--- FIND: START ---");
        Personne p2 = em.find(Personne.class, "Gripay");
        System.out.println(p2);
        System.out.println("--- FIND: END ---");
        
        System.out.println("--- SELECT: START ---");
        List<Personne> list = em.createQuery("Select s from Personne s").getResultList();
        for(Personne p : list) {
            System.out.println(p);
            LatLng coords1 = getLatLng(p.getAdresse());
            System.out.println("Coords: " + coords1.lat + " / " + coords1.lng);
        }
        System.out.println("--- SELECT: END ---");
        
        em.close();
    }
    
}
