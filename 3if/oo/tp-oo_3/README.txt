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

Note : pour des raisons de compatibilité avec Cygwin, les fonctions std::stoi ne
sont pas utilisées ; les stringstream et la fonction C atoi sont utilisés à la
place.

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

Le programme peut ensuite être compilé avec la commande "make".

Exécution
---------

La documentation des paramètres possibles est disponible en appelant tp-oo_3
avec l'option --help. Pour configurer d'autres options, il est également
possible de modifier le fichier optionnel tp-oo_3.cfg.

Les options qui peuvent être modifiées sont :

    - EXCLUDED_EXTENSIONS : la liste, séparée par des virgules, d'extensions à
      exclure du traitement lorsque l'option -e est spécifiée,

    - LOCAL_URL : l'URL du serveur local,

    - MAX_DOCUMENTS : le nombre de documents à afficher au maximum
