#include <sys/shm.h>

#include "Utils.h"

memoire_partagee_t * AttacherMemoirePartagee ( int semId, int shmId )
{
    sembuf verrouiller = SEM_MUTEX_VERROUILLER;
    while (semop(semId, &verrouiller, 1) < 0);
    return (memoire_partagee_t *) shmat(shmId, NULL, 0);
}

int DetacherMemoirePartagee ( int semId, const memoire_partagee_t * zone )
{
    shmdt(zone);
    sembuf deverrouiller = SEM_MUTEX_DEVERROUILLER;
    return semop(semId, &deverrouiller, 1);
}
