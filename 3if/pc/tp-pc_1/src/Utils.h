#if ! defined ( UTILS_H )
#define UTILS_H

#include "Config.h"

memoire_partagee_t * AttacherMemoirePartagee ( int semId, int shmId );

int DetacherMemoirePartagee ( int semId, const memoire_partagee_t * zone );

#endif // UTILS_H
