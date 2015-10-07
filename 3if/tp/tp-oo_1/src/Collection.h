/*************************************************************************
                           Collection  - Collection dynamique d'entiers
                             -------------------
    début                : 06/10/2015
    copyright            : (C) 2015 par B3309
*************************************************************************/

//---------- Interface de la classe Collection (fichier collection.cpp) ------
#if ! defined ( COLLECTION_H )
#define COLLECTION_H

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------------
// La classe Collection permet de gérer des collections d'entiers de taille
// quelconque fixée à la création avec réajustement automatique ou à la demande
//
//
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

    void Ajouter (int jeton);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Retirer (int n, int items[]);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Reunir (Collection* collection);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Ajuster (int n);
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur

    Collection (int n);
    // Mode d'emploi :
    //
    // Contrat :
    //

    Collection (int n, int items[]);
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

    void Init(int n);

//----------------------------------------------------- Attributs protégés
    int alloue;
    int elements;
    int* collection;

};

#endif // COLLECTION_H
