/*************************************************************************
            CollectionEntiers  - Collection dynamique d'entiers
                             -------------------
    début                : 06/10/2015
    copyright            : (C) 2015 par B3309
*************************************************************************/

// Interface de la classe <CollectionEntiers> (fichier CollectionEntiers.h)
#if ! defined ( COLLECTION_ENTIERS_H )
#define COLLECTION_ENTIERS_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <CollectionEntiers>
// La classe CollectionEntiers permet de gérer des collections d'entiers
// de taille quelconque fixée à la création avec réajustement automatique
// ou à la demande.
//------------------------------------------------------------------------

class CollectionEntiers
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Afficher ();
    // Mode d'emploi : Affiche le contenu de la collection.
    // Les valeurs sont séparées par des espaces.
    // Contrat : 'std::cout' doit exister et être accessible.

    void Ajouter (int valeur);
    // Mode d'emploi : Ajoute la valeur en paramètre à la collection.
    // Contrat : 'valeur' doit être un entier.

    void Retirer (unsigned int n, int retirer[]);
    // Mode d'emploi : Retire la liste de valeurs passée en paramètre de
    // la collection.
    // Contrat : 'n' doit spécifier la taille de 'retirer' ; 'retirer'
    // doit être un tableau d'entiers à retirer de la collection.

    void Reunir (CollectionEntiers * collection);
    // Mode d'emploi : Ajoute les valeurs de la collection passée en
    // paramètre à celles de cette collection.
    // Contrat : 'collection' doit être une CollectionEntiers bien
    // construite et initialisée.

    void Ajuster (unsigned int n);
    // Mode d'emploi : Modifie la taille de la collection pour qu'elle
    // prenne la taille 'n'. 'n' peut être supérieur ou inférieur à la
    // taille actulle (auquel cas la collection sera tronguée à partir de
    // la n-ième valeur incluse).
    // Contrat : 'n' doit être un entier strictement positif.

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    CollectionEntiers(unsigned int n);
    // Mode d'emploi : Construit une collection de taille 'n' sans valeurs
    // de départ (allocation seule).
    // Contrat : 'n' doit être un entier positif.

    CollectionEntiers(unsigned int n, int valeurs[]);
    // Mode d'emploi : Construit une collection de taille 'n' avec les
    // valeurs de départ du tableau 'valeurs'.
    // Contrat : 'n' doit spécifier la taille de 'valeurs' ; 'valeurs'
    // doit être un tableau d'entiers.

    virtual ~CollectionEntiers();
    // Mode d'emploi : Supprime le tableau de valeurs que contient la
    // 'collection'.
    // Contrat : N/A


//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Méthodes protégées

    void Init(unsigned int n);
    // Mode d'emploi : Initialise les valeurs de tous les attributs.
    // Contract : 'n' doit être un entier positif.

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
    unsigned int alloue;
    unsigned int elements;
    int * tableau;

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés
};

//-------------------------------- Types dépendants de <CollectionEntiers>

#endif // COLLECTION_ENTIERS_H
