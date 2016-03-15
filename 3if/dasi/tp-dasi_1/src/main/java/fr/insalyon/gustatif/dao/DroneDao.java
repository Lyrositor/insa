package fr.insalyon.gustatif.dao;

import fr.insalyon.gustatif.metier.modele.Drone;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;

public class DroneDao {

    public void create(Drone drone) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(drone);
        } catch (Exception e) {
            throw e;
        }
    }

    public Drone update(Drone drone) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            drone = em.merge(drone);
        } catch (Exception e) {
            throw e;
        }
        return drone;
    }

    public Drone findById(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Drone drone = null;
        try {
            drone = em.find(Drone.class, id);
        } catch (Exception e) {
            throw e;
        }
        return drone;
    }

    public List<Drone> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Drone> drones = null;
        try {
            Query q = em.createQuery("SELECT d FROM Drone d ORDER BY d.nom");
            drones = (List<Drone>) q.getResultList();
        } catch (Exception e) {
            throw e;
        }
        return drones;
    }
}
