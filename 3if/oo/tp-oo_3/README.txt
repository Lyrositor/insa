tp-oo_3
=======

Le TP OO 3 permet de lire un fichier de log d'Apache, d'en extraire les
documents parcourus et de traiter ces informations.

Auteurs : Marc Gagné et Selma Nemmaoui

Prérequis
---------
tp-oo_3 utilise des expressions régulières pour traiter les fichiers de log.
Pour ce faire, il faut soit :

  - la bibliothèque Boost.Regex (recommandé) : nos tests indiquent qu'elle
    assure les meilleurs performances,

  - un compilateur avec la bibliothèque regex de la STL : le support offert par
    les compilateurs pour les regex de la STL n'est pas uniforme ; nos tests
    avec GCC étaient moins performants qu'en utilisant Boost à la place.

La bibliothèque tclap (http://tclap.sourceforge.net/) est également utilisée
pour traiter les paramètres d'entrée ; celle-ci est fournie dans le dossier
include/, et ne nécessite pas de compilation séparée, n'étant constituée que de
fichiers d'interface. Elle a été légèrement modifiée pour réduire le nombre
d'avertissements qu'elle produit.

Compilation
-----------
Les définitions suivantes peuvent être utilisées lors de la compilation :

-DCOLORS    : active l'utilisation des couleurs à l'affichage (vert -> debug,
              jaune -> avertissement, rouge -> erreur)
-DMAP       : active l'affichage des messages de debug
-DNDEBUG    : désactive les assertions (inutiles ici)
-DUSE_BOOST : active l'utilisation de Boost.Regex ; si non spécifé, la
              bibliothèque regex de la STL sera utilisée à la place

Pour en ajouter ou en enlever, il suffit de modifier la variable DEFINITIONS de
Makefile.
