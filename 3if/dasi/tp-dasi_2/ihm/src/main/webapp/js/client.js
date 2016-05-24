/* --- Collect'IF Client Application --- */

/* Gestion des erreurs */
// Affiche un toast d'erreur avec la description donnée en paramètre
var afficherErreur = function($scope, $mdToast, description) {
  $scope.erreur = description;
  $mdToast.show({
    templateUrl: 'toast-erreur.html',
    scope: $scope,
    preserveScope: true,
    hideDelay: 3000,
    position: 'center'
  });
};

/* Gestion du chargement */
// Nécésite d'avoir ajouté la ligne suivante dans le code HTML :
// <md-progress-circular id="chargement" md-mode="indeterminate" style="display: none;"></md-progress-circular>
var chargement = function(afficher) {
  var iconeChargement = document.getElementById("chargement");
  if (iconeChargement !== null) {
    if(afficher === true) {
      document.getElementById("chargement").style.display = "block";
    } else {
      document.getElementById("chargement").style.display = "none";
    }
  }
};

/* Gestion de la déconnexion */
var deconnexion = function() {
  var request = new XMLHttpRequest();
  request.open('POST', './ActionServlet');
  request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
  request.onload = function() {
    window.location.replace('index.html');
  };
  request.send('action=deconnexion');
};

/* Angular Material */
var CollectIFClientApp = angular.module('CollectIFClientApp', ['ngMaterial', 'ngMessages']);

/* Index Controller */
CollectIFClientApp.controller('ClientIndexController', ['$scope', '$http', '$mdToast', function ($scope, $http, $mdToast) {
  $scope.user = new Object();
  $scope.user.email = '';

  $scope.user.submit = function() {
    // Si aucune e-mail n'est entrée
    if ($scope.user.email.length === 0) {
      afficherErreur($scope, $mdToast, 'E-mail vide.');
    } else {
      chargement(true);
      $http({
        method: 'POST',
        url: './ActionServlet',
        params: {
          action: 'authentification',
          email: $scope.user.email
        }
      }).then(function success(response) {
          console.log(response);
          var data = response.data;

          if (data.erreur === 'undefined') {
            afficherErreur($scope, $mdToast, 'Erreur de réception.');
          } else if (data.erreur) {
            afficherErreur($scope, $mdToast, data.erreur);
          } else {
            // Redirection
            window.location.replace('demandes.html');
          }

          chargement(false);
      }, function error(response) {
          console.log(response);
          afficherErreur($scope, $mdToast, 'Connexion impossible.');
          chargement(false);
      });
    }
  };
}]);

/* Inscription Controller */
CollectIFClientApp.controller('ClientInscriptionController', ['$scope', '$http', '$mdToast', function ($scope, $http, $mdToast) {
  $scope.user = new Object();
  $scope.user.nom = '';
  $scope.user.prenom = '';
  $scope.user.adresse = '';
  $scope.user.email = '';

  $scope.user.submit = function() {
    // Si aucune e-mail n'est entrée
    if ($scope.user.nom.length === 0) {
      afficherErreur($scope, $mdToast, 'Nom vide.');
    } else if ($scope.user.prenom.length === 0) {
      afficherErreur($scope, $mdToast, 'Prénom vide.');
    } else if ($scope.user.adresse.length === 0) {
      afficherErreur($scope, $mdToast, 'Adresse vide.');
    } else if ($scope.user.email.length === 0) {
      afficherErreur($scope, $mdToast, 'E-mail vide.');
    } else {
      chargement(true);
      $http({
        method: 'POST',
        url: './ActionServlet',
        params: {
          action: 'inscription',
          nom: $scope.user.nom,
          prenom: $scope.user.prenom,
          adresse: $scope.user.adresse,
          email: $scope.user.email
        }
      }).then(function success(response) {
          console.log(response);
          var data = response.data;

          if (data.erreur === 'undefined') {
            afficherErreur($scope, $mdToast, 'Erreur de réception.');
          } else if (data.erreur) {
            afficherErreur($scope, $mdToast, data.erreur);
          } else {
            // Redirection
            window.location.replace('index.html');
          }
          chargement(false);
      }, function error(response) {
          console.log(response);
          afficherErreur($scope, $mdToast, 'Inscription impossible.');
          chargement(false);
      });
    }
  };
}]);

/* Demandes Controller */
CollectIFClientApp.controller('ClientDemandesController', ['$scope', '$http', '$mdToast', function ($scope, $http, $mdToast) {
  $scope.date = new Date();
  $scope.list = new Object();
  $scope.list.activites = '';
  $scope.list.demandes = '';
  $scope.user = new Object();
  $scope.user.activite = '';
  $scope.user.date = new Date();
  $scope.formatDate = function(date) {
    var dateOut = new Date(date);
    return dateOut;
  };

  /* Chargement de la liste des activités */
  $http({
    method: 'POST',
    url: './ActionServlet',
    params: {
      action: 'listeActivites'
    }
  }).then(function success(response) {
      console.log(response);
      var data = response.data;

      if (data.erreur === 'undefined') {
            afficherErreur($scope, $mdToast, 'Erreur de réception.');
      } else if (data.erreur) {
        afficherErreur($scope, $mdToast, data.erreur);
      } else {
        $scope.list.activites = data.sort(function(a, b) {
          return  a.denomination.localeCompare(b.denomination);
        });
      }
      chargement(false);
  }, function error(response) {
      console.log(response);
      afficherErreur($scope, $mdToast, 'Récupération de la liste des activités impossible.');
      chargement(false);
  });

  /* Chargement de la liste des demandes */
  var listeDemande = function() {
    $http({
        method: 'POST',
        url: './ActionServlet',
        params: {
          action: 'listeDemandes'
        }
      }).then(function success(response) {
          console.log(response);
          var data = response.data;

          if (data.erreur === 'undefined') {
            afficherErreur($scope, $mdToast, 'Erreur de réception.');
          } else if (data.erreur) {
            afficherErreur($scope, $mdToast, data.erreur);
          } else {
            data.forEach(function(demande) {
              if (typeof demande.evenement === 'undefined') {
                demande.evenement = new Object();
                demande.evenement.planifie = 'Pas encore';
                demande.evenement.lieu = 'Non assigné';
              }
            });
            $scope.list.demandes = data;
          }
          chargement(false);
      }, function error(response) {
          console.log(response);
          afficherErreur($scope, $mdToast, 'Récupération de la liste des activités impossible.');
          chargement(false);
      });
  };
  listeDemande();

  /* Submit : effectuer une nouvelle demande */
  $scope.user.submit = function() {
    // S'il n'y a pas d'activité
    if ($scope.user.activite.length === 0) {
      afficherErreur($scope, $mdToast, 'Activité vide.');
      return;
    }

    chargement(true);
    $http({
      method: 'POST',
      url: './ActionServlet',
      params: {
        action: 'effectuerDemande',
        activite: $scope.user.activite,
        date: $scope.user.date.valueOf()
      }
    }).then(function success(response) {
        console.log(response);
        var data = response.data;

        if (data.erreur === 'undefined') {
            afficherErreur($scope, $mdToast, 'Erreur de réception.');
          } else if (data.erreur) {
          afficherErreur($scope, $mdToast, data.erreur);
        } else {
          // Rechargement
          listeDemande();
        }
        chargement(false);
    }, function error(response) {
        console.log(response);
        afficherErreur($scope, $mdToast, 'Récupération de la liste des demandes impossible.');
        chargement(false);
    });
  };
}]);

CollectIFClientApp.controller('ClientDetailsCtrl', ['$scope', '$http', '$mdToast', '$window', function ($scope, $http, $mdToast, $window) {
  $scope.formatDate = function(date) {
    var dateOut = new Date(date);
    return dateOut;
  };

    $scope.redirect = function(url) {
        $window.location.href = url;
    };

    var demande = location.search.split('demande=')[1];

    $http({
        method: 'POST',
        url: './ActionServlet',
        params: {
          action: 'getDemande',
          demande: demande
        }
      }).then(function success(response) {
          console.log(response);
          var data = response.data;

          if (data.erreur === 'undefined') {
            afficherErreur($scope, $mdToast, 'Erreur de réception.');
          } else if (data.erreur) {
            afficherErreur($scope, $mdToast, data.erreur);
          } else {
            console.log(data);
            $scope.demande = data;
          }
      }, function error(response) {
          console.log(response);
          afficherErreur($scope, $mdToast, 'Récupération de la liste des demandes impossible.');
          chargement(false);
      });

    $scope.map = { center: { latitude: 45, longitude: -73 }, zoom: 8 };
}]);