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
  if(iconeChargement != null) {
    if(afficher === true) {
      document.getElementById("chargement").style.display = "block";
    } else {
      document.getElementById("chargement").style.display = "none";
    }
  }
};

/* Angular Material */
var collectIFClientApp = angular.module('CollectIFClientApp', ['ngMaterial', 'ngMessages']);

/* Index Controller */
collectIFClientApp.controller('ClientIndexController', ['$scope', '$http', '$mdToast', function ($scope, $http, $mdToast) {
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

          if (data.erreur) {
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
collectIFClientApp.controller('ClientInscriptionController', ['$scope', '$http', '$mdToast', function ($scope, $http, $mdToast) {
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

          if (data.erreur) {
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
collectIFClientApp.controller('ClientDemandesController', ['$scope', '$http', '$mdToast', function ($scope, $http, $mdToast) {
  $scope.date = new Date();
  $scope.user = new Object();
  $scope.user.activite = '';

  $http({
        method: 'POST',
        url: './ActionServlet',
        params: {
          action: 'listeActivite',
        }
      }).then(function success(response) {
          console.log(response);
          var data = response.data;

          if (data.erreur) {
            afficherErreur($scope, $mdToast, data.erreur);
          } else {
            $scope.user.activite = data.sort(function(a, b) {
              return  a.denomination.localeCompare(b.denomination);
            });
          }
          chargement(false);
      }, function error(response) {
          console.log(response);
          afficherErreur($scope, $mdToast, 'Récupération de la liste des activités impossible.');
          chargement(false);
      });
}]);

CollectIFClientApp.controller('ClientDetailsCtrl', ['$scope', '$http', '$window',
    function ($scope, $http, $window) {
        $scope.redirect = function(url) {
            $window.location.href = url;
        }

        $scope.demande = {
            activite: "Tarot",
            personnes: 5,
            equipes: false,
            date: new Date(),
            evenement: {
                adresse: null,
                coordonnees: null
            }
        };

        $scope.map = { center: { latitude: 45, longitude: -73 }, zoom: 8 };
}]);