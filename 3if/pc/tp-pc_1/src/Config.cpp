#include "Config.h"

const struct sembuf SEM_MUTEX_VERROUILLER = {SEM_MUTEX, -1, 0};
const struct sembuf SEM_MUTEX_DEVERROUILLER = {SEM_MUTEX, 1, 0};
const struct sembuf SEM_BARRIERE_RESERVER = {AUCUNE, -1, 0};
const struct sembuf SEM_BARRIERE_AUTORISER = {AUCUNE, 1, 0};
