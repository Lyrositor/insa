#include <iostream>

using namespace std;

#include "collection.h"

int main()
{
    int elements[] = {5, 8, 19, 23, 0};
    Collection* c = new Collection(5, elements);
    c->Ajouter(12);
    c->Ajouter(13);
    c->Afficher();
    return 0;
}

