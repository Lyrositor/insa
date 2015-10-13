/*************************************************************************
               Collection  - Collection dynamique d'entiers
                             -------------------
    début                : 06/10/2015
    copyright            : (C) 2015 par B3309
*************************************************************************/

//------------- Interface de la classe <Collection> (fichier Collection.h)
#if ! defined ( COLLECTION_H )
#define COLLECTION_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Collection>
// La classe Collection permet de gérer des collections d'entiers de
// taille quelconque fixée à la création avec réajustement automatique ou
// à la demande.
//------------------------------------------------------------------------

class Collection
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Afficher ();
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Ajouter (int valeur);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Retirer (unsigned int n, int retirer[]);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Reunir (Collection* collection);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Ajuster (unsigned int n);
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    Collection (unsigned int n);
    // Mode d'emploi :
    //
    // Contrat :
    //

    Collection (unsigned int n, int items[]);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Collection ();
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Méthodes protégées

    void Init(unsigned int n);

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
    unsigned int alloue;
    unsigned int elements;
    int* tableau;

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés
};

//--------------------------------------- Types dépendants de <Collection>

#endif // COLLECTION_H
