/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package metier.modele;

import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import javax.persistence.Entity;
import javax.persistence.ManyToMany;

/**
 *
 * @author ovicente
 */
@Entity
public class EvenementAvecEquipe extends Evenement {
 
    @ManyToMany
    private List<Adherent> equipeA;
    @ManyToMany
    private List<Adherent> equipeB;
    
    protected EvenementAvecEquipe(){}
    
    public EvenementAvecEquipe(Date date, Activite activite, List<Demande> demandes) {
        super(date, activite, demandes);
        boolean a = true;
        equipeA = new LinkedList<Adherent>();
        equipeB = new LinkedList<Adherent>();
        for(Demande d : demandes) {
            if(a) {
                equipeA.add(d.getAdherent());
                a = false;
            } else {
                equipeB.add(d.getAdherent());
                a = true;
            }
        }
    }

    public List<Adherent> getEquipeA() {
        return equipeA;
    }

    public void setEquipeA(List<Adherent> equipeA) {
        this.equipeA = equipeA;
    }

    public List<Adherent> getEquipeB() {
        return equipeB;
    }

    public void setEquipeB(List<Adherent> equipeB) {
        this.equipeB = equipeB;
    }

    @Override
    public String toString() {
        return super.toString() + "EvenementAvecEquipe{" + "equipeA=" + equipeA + ", equipeB=" + equipeB + '}';
    }
    
    
    
}
