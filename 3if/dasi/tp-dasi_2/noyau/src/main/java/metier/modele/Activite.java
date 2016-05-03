package metier.modele;

import java.io.Serializable;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
public class Activite implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;
    private String denomination;
    private Boolean parEquipe;
    private Integer nbParticipants;

    public Activite() {
    }

    public Activite(String denomination, Boolean parEquipe, Integer nbParticipants) {
        this.denomination = denomination;
        this.parEquipe = parEquipe;
        this.nbParticipants = nbParticipants;
    }

    public Integer getId() {
        return id;
    }

    public String getDenomination() {
        return denomination;
    }

    public Boolean isParEquipe() {
        return parEquipe;
    }

    public Integer getNbParticipants() {
        return nbParticipants;
    }

    public void setDenomination(String denomination) {
        this.denomination = denomination;
    }

    public void setParEquipe(Boolean parEquipe) {
        this.parEquipe = parEquipe;
    }

    public void setNbParticipants(Integer nbParticipants) {
        this.nbParticipants = nbParticipants;
    }

    @Override
    public String toString() {
        return "Activite{" + "id=" + id + ", denomination=" + denomination + ", parEquipe=" + parEquipe + ", nbParticipants=" + nbParticipants + '}';
    }
       
}
