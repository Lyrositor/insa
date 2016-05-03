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
public class EvenementSansEquipe extends Evenement {
    
    @ManyToMany
    private List<Adherent> participants;
    
    protected EvenementSansEquipe(){}
    
    public EvenementSansEquipe(Date date, Activite activite, List<Demande> demandes) {
        super(date, activite, demandes);
        participants = new LinkedList<Adherent>();
        for(Demande d : demandes) {
            participants.add(d.getAdherent());
        }
    } 

    public List<Adherent> getParticipants() {
        return participants;
    }

    public void setParticipants(List<Adherent> participants) {
        this.participants = participants;
    }

    @Override
    public String toString() {
        return super.toString() + "EvenementSansEquipe{" + "participants=" + participants + '}';
    }
    
    
}
