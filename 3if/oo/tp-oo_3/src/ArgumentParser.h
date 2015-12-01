/*************************************************************************
       ArgumentParser  - Traiteur d'arguments de ligne de commande
                             -------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*************************************************************************/

// Interface de la classe <ArgumentParser> (fichier ArgumentParser.h)
#if ! defined ( ARGUMENT_PARSER_H )
#define ARGUMENT_PARSER_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <ArgumentParser>
//
//------------------------------------------------------------------------

class ArgumentParser {
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void addArgument ();
    // Mode d'emploi :
    // Contrat :

    void addOption ();
    // Mode d'emploi :
    // Contrat :

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    ArgumentParser ();
    // Mode d'emploi :
    // Contrat :

    virtual ~ArgumentParser ();
    // Mode d'emploi :
    // Contrat : N/A


//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés
};

//----------------------------------- Types dépendants de <ArgumentParser>

#endif // ARGUMENT_PARSER_H
